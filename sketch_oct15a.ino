#include  <Servo.h>
#include <ArduinoJson.h>
int danger = 0;
Servo myservo;
int pos = 0;
int servo_flag=1;
int m1_flag=0;
int Vo;
float R1 = 9200;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
const int currentPin = A2;
int sensitivity = 66;
int adcValue= 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
double currentValue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(12, INPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(13, INPUT);
  Serial.begin(9600);
  myservo.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  danger = 0;
  if (digitalRead(13) == 1)
    digitalWrite(9, HIGH);
  else if (digitalRead(13) == 0)
    digitalWrite(9,LOW);
    
  Vo = analogRead(A1);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15; 
  T = (T * 9.0)/ 5.0 + 32.0; 
  T = T-50.0;

  if (T>40)
  {
    digitalWrite(9, LOW);
    digitalWrite(8, HIGH);
    danger = 1;
    delay(10000);
    
    digitalWrite(8, LOW);
  }

  if (digitalRead(12)==1)
  {
    digitalWrite(11, HIGH);
  }

  else
  {
    digitalWrite(11, LOW);
  }
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to po4sition in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }


  
  adcValue = analogRead(currentPin);
  adcVoltage = (adcValue / 1024.0) * 5;
//  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
  

//Serial.print("temperature: ");
//Serial.print(T);
//Serial.print("current: ");
StaticJsonDocument<200> doc;
doc["current"]=adcVoltage;
doc["temp"]=T;
doc["danger"]= danger;
serializeJson(doc,Serial);
//Serial.println(adcVoltage);
Serial.println();
delay(200);

}
