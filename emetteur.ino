
#include <VirtualWire.h>
#include <MPU6050.h>
#include <I2Cdev.h>

MPU6050 mpu ;

int16_t ax, ay, az ;
int16_t gx, gy ,gz ;

void setup() 
{

Serial.begin(9600);
vw_setup(2000);
mpu.initialize();
Serial.println(mpu.testConnection()? " YES " : " NO " );
delay(1000);
Serial.println("Capt values from sensor");
delay(1000);
}

void loop() {
  
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  float a = map(ax, -17000, 17000, -90, 90);
  float b = map(az, -1700,1700, 750,2250);
  float tab[2];
  tab[0] = a;
  tab[1] = b;
  
  vw_send((byte *) &tab, sizeof(tab));      ///On envoie le message
  vw_wait_tx();                                   ///On attend la fin de l'envoi
}

