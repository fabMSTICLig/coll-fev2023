//Code pour le projet cible du stage de collégiens de Persyval 2023

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//Bibliotèque pour l'écran LCD
#include "HD44780_LCD_PCF8574.h"

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 5
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


HD44780LCD myLCD( 4, 20, 0x27); // instantiate an object
// tableau permettant d'enregistrer la couleur de chaque LED
uint32_t ledt [5] = {0};
// tableau de sauvegarder la valeur des capteurs au démarage de la arduino
int svd [5] = {0};
//seuil lumiere
int seuil = 50;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin();
  pixels.clear();

  myLCD.PCF8574_LCDInit(LCDCursorTypeOff);
  myLCD.PCF8574_LCDClearScreen();
  myLCD.PCF8574_LCDBackLightSet(true);
  
  pinMode(3, INPUT_PULLUP);

  //Chois des couleur pour chaque LED
  ledt[0] = pixels.Color(150, 0, 150);
  ledt[1] = pixels.Color (25, 0, 150);
  ledt[2] = pixels.Color (150, 50, 0);
  ledt[3] = pixels.Color (0, 150, 25);
  ledt[4] = pixels.Color (150, 150, 150);

  //Initialisation de l'écran LCD
  myLCD.PCF8574_LCDClearScreen();

  //Callibrage des capteurs
  myLCD.PCF8574_LCDGOTO(LCDLineNumberOne, 0);
  myLCD.print("Calibrage");
  delay(10000);
  svd[0] = analogRead(A0);
  svd[2] = analogRead(A2);
  svd[1] = analogRead(A1);
  svd[3] = analogRead(A3);
  svd[4] = analogRead(A4);

  //Text de démarage de la cible
  myLCD.PCF8574_LCDClearScreen();
  myLCD.PCF8574_LCDGOTO(LCDLineNumberOne, 0);
  myLCD.print("Appuyez sur");
  myLCD.PCF8574_LCDGOTO(LCDLineNumberTwo, 0);
  myLCD.print("le bouton");
  myLCD.PCF8574_LCDGOTO(LCDLineNumberThree, 0);
  myLCD.print("pour commencer");
}

void loop() {

  //Attente de l'appui de boutton (En pullup donc on attent LOW)
  while (digitalRead(3) == HIGH) {
    delay(50);
  }
  //On éteint les lumières et on efface l'écran
  pixels.clear();
  pixels.show();
  myLCD.PCF8574_LCDClearScreen();

  
  myLCD.PCF8574_LCDGOTO(LCDLineNumberOne, 0);
  myLCD.print("Debut partie");

  int varal = random(5) + 5;
  delay(varal*1000);

  //Sauvegarde du temps
  uint32_t vart = millis();
  
  //Indice tableau
  int idT = random(4);
  
  myLCD.PCF8574_LCDGOTO(LCDLineNumberTwo, 0);
  myLCD.print("Cible ");
  myLCD.print(idT+1);
  
  pixels.setPixelColor(idT, ledt[idT]);
  pixels.show();

  int svt [5] = {0};
  int i = 5;
  while (i == 5) {
    svt[0] = analogRead(A0);
    svt[2] = analogRead(A2);
    svt[1] = analogRead(A1);
    svt[3] = analogRead(A3);
    svt[4] = analogRead(A4);
    if (svt [0] - svd[0] > seuil) {
      i = 0;
    }
    if (svt [1] - svd[1] > seuil) {
      i = 1;
    }
    if (svt [2] - svd[2] > seuil) {
      i = 2;
    }
    if (svt [3] - svd[3] > seuil) {
      i = 3;
    }
    if (svt [4] - svd[4] > seuil) {
      i = 4;
    }
  }
  for (int y = 0; y < 5; y++)
  {
    pixels.setPixelColor(y, ledt[y]);
  }
  pixels.show();

  vart = millis() - vart;
  myLCD.PCF8574_LCDClearScreen();
  myLCD.PCF8574_LCDGOTO(LCDLineNumberTwo, 0);
  if (i == idT) {
      myLCD.print("Bonne cible");
  }
  else
  {
      myLCD.print("Mauvaise cible");
  }
  myLCD.PCF8574_LCDGOTO(LCDLineNumberThree, 0);
  myLCD.print("Temps : ");
  myLCD.print(vart/1000.0,3);
  
}
