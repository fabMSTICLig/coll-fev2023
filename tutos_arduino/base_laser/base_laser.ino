
// DEFINITION DES PINS DE CONNEXION
#define LASER_PIN     2
#define LUM_PIN       A1
#define BOUTON_PIN    7


void setup()
{
   ///////////INITIALISATION
   // initialisation moniteur serie
   Serial.begin(9600);

  // initialisation capteur luminosité
   pinMode(LUM_PIN, INPUT);
   analogWrite(LUM_PIN, LOW);

// initialisation laser
  pinMode(LASER_PIN, OUTPUT);

 // initialisation bouton
 pinMode(BOUTON_PIN,INPUT); 
}


void stop_laser()
{
    digitalWrite(LASER_PIN, 0);
}

void start_laser()
{
    digitalWrite(LASER_PIN, 1);
}

void loop()
{
   long light = analogRead(LUM_PIN);
   Serial.print("capteur lumière = ");
   Serial.println(light);

    if (digitalRead(BOUTON_PIN) != 0)
    {
      Serial.println("boutton préssé");
      start_laser();
    }
    else
    {
      stop_laser();
    }
}
