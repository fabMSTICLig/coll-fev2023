#include <IRremote.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>


// DEFINITION DES PINS DE CONNEXION
#define IR_PIN        8
//#define LASER_PIN     2
//#define LUM_PIN       A1


// DEFINITION DES BOUTONS DE LA TELECOMMANDE
#define FLECHE_HAUT   0x46
#define FLECHE_BAS    0x15
#define FLECHE_GAUCHE 0x44
#define FLECHE_DROITE 0x43
#define TOUCHE_1      0x16
#define TOUCHE_2      0x19
#define TOUCHE_3      0xD
#define TOUCHE_4      0xC
#define TOUCHE_5      0x18
#define TOUCHE_6      0x5E
#define TOUCHE_7      0x8
#define TOUCHE_8      0x1C
#define TOUCHE_9      0x5A
#define TOUCHE_0      0x52
#define TOUCHE_ETOILE 0x42
#define TOUCHE_DIESE  0x4A
#define TOUCHE_OK     0x40

// DELAI MAXIMUM AVANT EXTINCTION DU LASER EN mili seconde
#define MAX_DURATION 800


long timevar = 0;

//
//
//void stop_laser()
//{
//    digitalWrite(LASER_PIN, 0);
//}
//
//void start_laser()
//{
//    digitalWrite(LASER_PIN, 1);
//}


void setup()
{
  ///////////INITIALISATION
  // initialisation moniteur serie
  Serial.begin(9600);
  
  // initialisation infra rouge
  Serial.println("Enabling IR");
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Enabled IR");

  // initialisation nombres aléatoires
   randomSeed(analogRead(A2));

  // initialisation capteur luminosité
//  pinMode(LUM_PIN, INPUT);
//  analogWrite(LUM_PIN, LOW);

  // initialisation laser 
//  pinMode(LASER_PIN, OUTPUT);


  
  /////////// FIN D'INITIALISATION 
}

void loop()
{

  int nombre_aleatoire = random(0, 200);



//int light = analogRead(A1);
//   Serial.print("Light = ");
//   Serial.println(light);


   


  if (IrReceiver.decode())
  {
//        IrReceiver.printIRResultShort(&Serial);
    if (IrReceiver.decodedIRData.command == FLECHE_HAUT)
    {
        Serial.println("touche: FLECHE_HAUT");

    }
    else if (IrReceiver.decodedIRData.command == FLECHE_BAS)
    {
        Serial.println("touche: FLECHE_BAS");

    }
    else if (IrReceiver.decodedIRData.command == FLECHE_GAUCHE)
    {
        Serial.println("touche: FLECHE_GAUCHE");

    }
    else if (IrReceiver.decodedIRData.command == FLECHE_DROITE)
    {
        Serial.println("touche: FLECHE_DROITE");

    }
    else if (IrReceiver.decodedIRData.command == TOUCHE_1)
    {
        Serial.println("touche: TOUCHE_1");

    }
    else if (IrReceiver.decodedIRData.command == TOUCHE_2)
    {
        Serial.println("touche: TOUCHE_2");

    }
    else if (IrReceiver.decodedIRData.command == TOUCHE_3)
    {
        Serial.println("touche: TOUCHE_3");

    }
    else if (IrReceiver.decodedIRData.command == TOUCHE_4)
    {
        Serial.println("touche: TOUCHE_4");

    }
    else if (IrReceiver.decodedIRData.command == TOUCHE_5)
    {
        Serial.println("touche: TOUCHE_5");

    }
    else if (IrReceiver.decodedIRData.command == TOUCHE_6)
    {
        Serial.println("touche: TOUCHE_6");

    }
    else if (IrReceiver.decodedIRData.command == TOUCHE_7)
    {
        Serial.println("touche: TOUCHE_7");

    }
    else if (IrReceiver.decodedIRData.command == TOUCHE_8)
    {
        Serial.println("touche: TOUCHE_8");

    }
    else if (IrReceiver.decodedIRData.command == TOUCHE_9)
    {
        Serial.println("touche: TOUCHE_9");

    }
    else if (IrReceiver.decodedIRData.command == TOUCHE_0)
    {
        Serial.println("touche: TOUCHE_0");

    }
    else if (IrReceiver.decodedIRData.command == TOUCHE_ETOILE)
    {
        Serial.println("touche: TOUCHE_ETOILE");

    }
    else if (IrReceiver.decodedIRData.command == TOUCHE_DIESE)
    {
        Serial.println("touche: TOUCHE_DIESE");

    }
    else if (IrReceiver.decodedIRData.command == TOUCHE_OK)
    {
        Serial.println("touche: TOUCHE_OK");

    }
    IrReceiver.resume();
  }


if (millis() - timevar > MAX_DURATION)
  {
    
    timevar = millis();
    IrReceiver.stop();
//    stop_laser();
    IrReceiver.start();
  }


}
