#include <AFMotor.h>

         /// motor shield
#include "ServoTimer2.h"      /// servomotor
#include <VirtualWire.h>     /// emetteur recepteur 433Mhz


AF_DCMotor motor(2);       /// le moteur est en 2
ServoTimer2 myservo;      /// on définit le servo "myservo"


float valeur[2];        /// on défnit le tableau "valeur" pour tout le programme

void setup() 
{
  
  Serial.begin(9600);
  myservo.attach(31);     /// Servo attaché au pin 31
  vw_set_rx_pin(23);     /// Modification du pin par défaut du récepteur car déjà occupé par le motorshield
 
  vw_setup(2000);
  vw_rx_start();
  Serial.println("Recepteur");
 
}

void loop() 
{
  byte taille_message = sizeof(valeur);
 
  vw_wait_rx();                                              /// On attend la reception d'un message
    if (vw_get_message((byte *) &valeur, &taille_message))
    {
    Serial.print("valeur[0]=");
    Serial.println(valeur[0]);                              /// Affiche le message
    Serial.print("valeur[1]=");
    Serial.println(valeur[1]);     
    moteur();
    servo();
    }
}


                ///////////////// Ajout du code moteur & servomoteur \\\\\\\\\\\\\\\\\\\\\\\


void moteur()
{
  if (valeur[0] >0)
  {
    motor.run(FORWARD);
    int a = map(valeur[0], 1,90, 1, 255);
    motor.setSpeed(a);
  }
  
  else 
  {
    motor.run(BACKWARD);
    int a = map(valeur[0], -1,-90, 1, 255);
    motor.setSpeed(a);
  }
}


void servo()
{
  int b = valeur[1];     
  myservo.write(b);
}


