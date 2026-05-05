#include <IRremote.h>
#include <MPU9255.h>

MPU9255 mpu;

byte led = 7;
byte motor = A2;
byte IR = A0;


char remoteDecoder(unsigned long data) {
  Serial.print("Received: ");
  Serial.println(data, HEX); // Prints in Hex so you can see the code clearly
  switch(data){
    case 46: 
      delay(500);
      return '1';
    case 0xB942: 
      delay(500);
      return '1';
    case 0:
      return '0';
    default:
      delay(500);
      return '1';
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);

  IrReceiver.begin(IR, ENABLE_LED_FEEDBACK);

  pinMode(led, OUTPUT);
  pinMode(motor, OUTPUT);
  Serial.print("serial monitor  == #ON!");
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
  // put your main code here, to run repeatedly:
  static bool start = 0;
  static int prevAcc = 0;
  if(IrReceiver.decode()){
    long int data_remote = IrReceiver.decodedIRData.command;
    char signal = remoteDecoder(data_remote);
    Serial.println(signal);

  if(signal != '0'){
    if(signal == '1'){
      Serial.println("up");
      delay(500);
      start = 1;
    }
    }
  }
  //start = 1;
  if(start){
    digitalWrite(motor, HIGH);
  }
  else{
    digitalWrite(motor,LOW);
  }
  mpu.read_acc();//get data from the accelerometer
  if (millis() % 10 == 0){
  //print all data in serial monitor
    Serial.print("AY: ");
    Serial.println(mpu.ay);
    delay(1);
  }
if(prevAcc - mpu.ay > 2000){
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      delay(100);
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      delay(100);
      Serial.println("Beep Beep!");
      delay(1000);
    }
  else{
    delay(10);
  }
  prevAcc = mpu.ay;
}