/*
This code:
    1- reads AquaClean Pro's distance sensor and decides a-keep moving  b-turn

Last update by: Nermeen M. Saleh      @ 03/05/2024
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(14,13); // RX, TX
unsigned char data[4]={};
float distance;
int safeDistance = 400; //safe distance to turn around in mm
bool turn = false;

void setup()
{
 Serial.begin(57600);
 mySerial.begin(9600); 
}

void loop()
{
    do{
     for(int i=0;i<4;i++)
     {
       data[i]=mySerial.read();
     }
  }while(mySerial.read()==0xff);

  mySerial.flush();

  if(data[0]==0xff)
    {
      int sum;
      sum=(data[0]+data[1]+data[2])&0x00FF;
      if(sum==data[3])
      {
        distance=(data[1]<<8)+data[2];
        if(distance>safeDistance)
          { 
           turn = false;
           //Serial.print(turn);
           Serial.print("Keep going distance= ");
           Serial.print(distance/10);
           Serial.println(" cm");
          }else 
             {
               turn = true;
               //Serial.print(turn);
               Serial.print("TURN NOW! distance= ");
               Serial.print(distance/10);
               Serial.println(" cm");
             }
      }else Serial.println("ERROR");
     }
     delay(100);
}

