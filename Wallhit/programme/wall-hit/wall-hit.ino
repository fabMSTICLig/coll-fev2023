#include <IRremote.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
// ^ include des 3 library:
// - infra rouge (IRremote.h) 
// - servo moteurs (Servo.h)
// - Ruban de leds (Adafruit_NeoPixel.h)

// DEFINITION PIN DE CONNEXION DU CAPTEUR INFRA ROUGE
#define IR_PIN        8

//DEFINITION PIN SERVO
#define SERVO1_PIN 9
#define SERVO2_PIN 7

// DEFINITION PIN LEDS
#define LED_PIN    A0

// DEFINITION NOMBRE DE LEDS
#define LED_COUNT  5

// DEFINITION DES PINS DE CONNEXION DU LAESR
#define LASER_PIN     2

//DEFINITION PIN CAPTEURS DE LUMIERE
#define LUM_PIN       A1
#define LUM_PIN2      A2

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

// variable "myservo1" et "myservo2" pour manipuler les servo moteurs
Servo myservo1;
Servo myservo2;

// variable "timervar" pour mesurer le temps ecouler avant d'eteindre le laser
long timevar = 0;
// variable "timervar2" pour mesurer le temps ecouler après "mort" du robot
long timevar2 = 0;
// variable "mode_auto" 
int mode_auto = 0;
// variable "nombre_aleatoire" contenant un nombre aléatoire modifié à chaque tour de la fonction loop()
int nombre_aleatoire = 0;

// variable "strip" pour manipuler le ruban de leds
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    //////////////////// INITIALISATION ////////////////////
    
    // initialisation moniteur serie
    Serial.begin(9600);

    // initialisation leds
    strip.begin();
    strip.show();
    strip.setBrightness(50);
    
    // initialisation infra rouge
    Serial.println("Enabling IR");
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
    Serial.println("Enabled IR");

    // initialisation nombres aléatoires
    randomSeed(analogRead(A2));

    // initialisation servo
    myservo1.attach(SERVO1_PIN);
    myservo2.attach(SERVO2_PIN);

    // initialisation capteur luminosité 1
    pinMode(LUM_PIN, INPUT);
    analogWrite(LUM_PIN, LOW);
    // initialisation capteur luminosité 2
    pinMode(LUM_PIN2, INPUT);
    analogWrite(LUM_PIN2, LOW);

    // initialisation laser
    pinMode(LASER_PIN, OUTPUT);
    //////////////////// FIN D'INITIALISATION ////////////////////
}

// Fonction "set_led_color" qui prend 3 parametres (3 variables numériques entre 0 et 255) et applique cette couleur aux leds
void set_led_color(int red, int green, int blue)
{
    // crée une varaible "color" qui contient les informations des niveau de rouge de vert et de bleu
    int32_t color = strip.Color(red, green, blue);
    Serial.print("set led color");
    // boucle "for" pour itérer sur chaque led du ruban
    for(int i = 0; i < strip.numPixels(); i = i + 1)
    {
        // defini la couleur "color" pour la led numero "i"
        strip.setPixelColor(i, color);
        // applilque la couleur definie
        strip.show();
        // pause de 0,150 seconde
        delay(150);
    }
}

// Fonction "eteindre_leds" qui eteind toutes les leds
void eteindre_leds()
{
    int32_t color = strip.Color(0, 0, 0);
    Serial.print("set led color");
    for(int i = 0; i < strip.numPixels(); i = i + 1)
    {
      strip.setPixelColor(i, color);
      strip.show();
    }
}

//Fonction "avancer" qui fait tourner les servomoteurs pour faire avancer le robot
void avancer()
{
    myservo1.write(181);
    myservo2.write(2);  
}

//Fonction "arreter" qui stop les servomoteurs pour arreter le robot
void arreter()
{
    myservo1.write(91);
    myservo2.write(92);  
}

//Fonction "Droite" qui fait tourner les servomoteurs pour faire tourner à droite le robot
void Droite()
{
    myservo1.write(181);
    myservo2.write(182);
}
//Fonction "Gauche" qui fait tourner les servomoteurs pour faire tourner à gauche le robot
void Gauche()
{   
    myservo1.write(1);
    myservo2.write(2);
}
//Fonction "Reculer" qui fait tourner les servomoteurs pour faire reculer le robot
void Reculer()
{
    myservo1.write(1);
    myservo2.write(182);
} 

// Fonction qui arrete le laser
void stop_laser()
{
    digitalWrite(LASER_PIN, 0);
}

// Fonction qui allume le laser
void start_laser()
{
    digitalWrite(LASER_PIN, 1);
}

// Fonction "Mort" qui arrete le depacement du robot et allume les leds en rouge pendant 5 secondes
void Mort()
{
    Serial.println("fonction Mort");
    arreter();
    stop_laser();
    set_led_color(255, 0, 0);
    // pause de 5 secondes
    delay(5 * 1000);
    eteindre_leds(); 
}


// Fonction "automatic_mode" qui appelle aléatoirement une fonction de deplacement en fonction de la valeur du nombre_aleatoire 
void  automatic_mode()
{
    // la fonction millis() retorune le temps ecoulé depuis l'allumage du Arduino ce qui permet de verifier si 1 seconde s'est écoulée avec la condition "millis() - timevar2 > 1000"
    if (millis() - timevar2 > 1000)
    {
        // appelle set_led_color avec 3 valeurs aléatoires entre 0 et 255
        set_led_color(random(0, 255), random(0, 255), random(0, 255));
        if (nombre_aleatoire == 0)
        {
           avancer();
        }
        else if (nombre_aleatoire == 1)
        {
            Reculer();
        }
        else if (nombre_aleatoire == 2)
        {
            Gauche();
        }
        else if (nombre_aleatoire == 3)
        {
            Droite();
        }
        else if (nombre_aleatoire == 4)
        {
            arreter();
        }
        // on met à jour la varriable timevar2 avec la valeur de temps actuel
        timevar2 = millis();
    }
}

void loop()
{
    // on lit les valeurs des capteurs de lumière
    long light = analogRead(LUM_PIN);
    long light2 = analogRead(LUM_PIN2);

    // on ecrit sur le moniteur les relevés des capteurs de lumière
    Serial.print("light1 = ");
    Serial.println(light);
    Serial.print("light2 = ");
    Serial.println(light2);

    // si laser capté sur capteur1 appel la fonction mort
    if(light >= 75)
    {
        Mort();
    }
    // si laser capté sur capteur2 appel la fonction mort
    if(light2 >= 75)
    {
        Mort();
    }
    // generation d'un nombre aléatoire entre 0 et 5
    nombre_aleatoire = random(0, 5);

    // si la variable mode_auto est differente de 0 appel de la fonction "automatic_mode"
    if (mode_auto != 0)
    {
        automatic_mode();
    }

    // si quelquechose a été recu par la capteur infrarouge
    if (IrReceiver.decode())
    {
        // test toutes les touches pour savoir la quelle à ete appuyé
        if (IrReceiver.decodedIRData.command == FLECHE_HAUT)
        {
            Serial.println("touche: FLECHE_HAUT");
            avancer();
        }
        else if (IrReceiver.decodedIRData.command == FLECHE_BAS)
        {
            Serial.println("touche: FLECHE_BAS");
            Reculer();
        }
        else if (IrReceiver.decodedIRData.command == FLECHE_GAUCHE)
        {
            Serial.println("touche: FLECHE_GAUCHE");
            Gauche();
        }
        else if (IrReceiver.decodedIRData.command == FLECHE_DROITE)
        {
            Serial.println("touche: FLECHE_DROITE");
            Droite();
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
            set_led_color(0, 255, 0);

        }
        else if (IrReceiver.decodedIRData.command == TOUCHE_8)
        {
            Serial.println("touche: TOUCHE_8");
            set_led_color(0, 0, 255);
        }
        else if (IrReceiver.decodedIRData.command == TOUCHE_9)
        {
            Serial.println("touche: TOUCHE_9");
            set_led_color(255, 0, 255);

        }
        else if (IrReceiver.decodedIRData.command == TOUCHE_0)
        {
            Serial.println("touche: TOUCHE_0");
            arreter();
        }
        else if (IrReceiver.decodedIRData.command == TOUCHE_ETOILE)
        {
            Serial.println("touche: TOUCHE_ETOILE");
            arreter();
            mode_auto = 0;
            eteindre_leds();
        }
        else if (IrReceiver.decodedIRData.command == TOUCHE_DIESE)
        {
            Serial.println("touche: TOUCHE_DIESE");
            mode_auto = 1;
        }
        else if (IrReceiver.decodedIRData.command == TOUCHE_OK)
        {
            start_laser();
            Serial.println("touche: TOUCHE_OK");
        }
        IrReceiver.resume();
    }

    // la fonction millis() retorune le temps ecoulé depuis l'allumage du Arduino ce qui permet de verifier si 0.8 seconde s'est écoulée avec la condition "millis() - timevar > 800"
    if (millis() - timevar > MAX_DURATION)
    {
        // on met à jour la variable timevar pour le prochaine appel
        timevar = millis();
        IrReceiver.stop();
        stop_laser();
        IrReceiver.start();
    }
}
