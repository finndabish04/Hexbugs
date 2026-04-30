/*
Raw data example
This example reads raw readings from the magnetometer gyroscope and the accelerometer and then
displays them in serial monitor.
*/

#include <MPU9255.h>//include MPU9255 library

MPU9255 mpu;
byte ledpin = 18;


void setup() {
  Serial.begin(115200);//initialize Serial port
  pinMode(ledpin, OUTPUT);

  if(mpu.init())
  {
  Serial.println("initialization failed");
  }
  else
  {
  Serial.println("initialization successful!");
  }

}

void loop() {
  mpu.read_acc();//get data from the accelerometer

  //print all data in serial monitor
  Serial.print("AY: ");
  Serial.println(mpu.ay);
  static int prevAcc = 0;
  delay(1);
  if(prevAcc - mpu.ay > 3000){
    digitalWrite(ledpin, HIGH);
    delay(100);
    digitalWrite(ledpin, LOW);
    delay(100);
    digitalWrite(ledpin, HIGH);
    delay(100);
    digitalWrite(ledpin, LOW);
    delay(100);
    Serial.println("Beep Beep!");
    delay(1000);
  }
  else{
    delay(10);
  }
  prevAcc = mpu.ay;
}

// old if statement
//  if(mpu.ay < 0 && prevAcc > 0)
