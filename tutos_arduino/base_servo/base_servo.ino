#include <Servo.h>

#define SERVO1_PIN 9
#define SECONDE 1000

Servo myservo1;


void setup()
{
  myservo1.attach(SERVO1_PIN);
}

void loop()
{
    myservo1.write(0);
    delay(5 * SECONDE);
    myservo1.write(180);
    delay(5 * SECONDE);
}
