#include "Wire.h"
#include <MPU6050_light.h>
#include <JQ6500_Serial.h>
JQ6500_Serial mp3(Serial);

MPU6050 mpu(Wire);
unsigned long timer = 0;
const int flexPin0 = A6; 
const int flexPin1 = A3;
const int flexPin2 = A2;
const int flexPin3 = A1;
const int flexPin6 = A0;

void setup() 
{ 
  Serial.begin(9600);
  Wire.begin();
  mpu.begin();
  Serial.println(F("Calculating gyro offset, do not move MPU6050"));
  delay(1000);
  mpu.calcGyroOffsets();
  Serial.println("Done!\n");
  mp3.reset();
  mp3.setVolume(30);
  mp3.setLoopMode(MP3_LOOP_NONE);

} 

void loop() 
{ 
  int THUMB;
    int INDEX;
     int MIDDLE;
      int RING;
       int LITTLE;
 THUMB  = analogRead(flexPin0);
   INDEX = analogRead(flexPin1);
    MIDDLE = analogRead(flexPin2);
     RING = analogRead(flexPin3);
      LITTLE = analogRead(flexPin6);
   Serial.print("THUMB: ");
   Serial.println(THUMB);
    Serial.print("INDEX: ");
    Serial.println(INDEX);
     Serial.print("MIDDLE: ");
     Serial.println(MIDDLE);
      Serial.print("RING: ");
      Serial.println(RING);
       Serial.print("LITTLE: ");
       Serial.println(LITTLE);
 
  delay(1000);
  mpu.update();
  
  if((millis()-timer)>100){ // print data every 10ms
  Serial.print("X : ");
  Serial.print(mpu.getAngleX());
  Serial.print("\tY : ");
  Serial.print(mpu.getAngleY());
  Serial.print("\tZ : ");
  Serial.println(mpu.getAngleZ());
  timer = millis();  }
 
   if(mp3.getStatus() != MP3_STATUS_PLAYING)
{
  if 
  ((THUMB<350))
  {
     mp3.playFileByIndexNumber(1);
         Serial.print("ME");
}
  else if
  ((INDEX<350))
  {
     mp3.playFileByIndexNumber(2);
         Serial.print("YOU");
}
 
  else if
  
((mpu.getAngleY()<-25))
  {
    mp3.playFileByIndexNumber(3);  
        Serial.print("hello");
       
  }
  else if
  
((mpu.getAngleY()>25))
  {
    mp3.playFileByIndexNumber(3);  
        Serial.print("hello");
       
  }
 else 
 {
  Serial.print("NO INPUT");
 }
}
}
