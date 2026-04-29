//#include "TinyWireM.h"

#include <MPU9255.h>
#include <Arduino.h>
MPU9255 mpu;
#define g 9.81

int ledpin = 18;

void setup() {
  Serial.begin(115200);
  Serial.println("Serial working! :)");
  pinMode(ledpin, OUTPUT);
}

void loop() {

  mpu.set_acc_scale(scale_2g);
  mpu.read_acc();

  double ax_g = (mpu.ax / 32768.0) * 2 * g;
  Serial.println(ax_g);
  Serial.print("raw data: ");
  Serial.print(mpu.ax);
  Serial.print(" ");
  Serial.print(mpu.ay);
  Serial.print(" ");
  Serial.println(mpu.az);
  
  // if(ax_g > 1.0){
  //   digitalWrite(ledpin, HIGH);
  //   delay(100);
  //   digitalWrite(ledpin, LOW);
  //   delay(100);
  //   digitalWrite(ledpin, HIGH);
  //   delay(100);
  //   digitalWrite(ledpin, LOW);
  //   delay(100);
  // }
  // else{
  //   digitalWrite(ledpin, HIGH);
  //   delay(500);
  //   digitalWrite(ledpin, LOW);
  // }
  
  delay(500);


}
