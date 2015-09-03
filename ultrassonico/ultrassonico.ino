#include <Servo.h>
#define trigPin 13
#define echoPin 12
Servo SERVO;
int sensorESQ = A0;
int sensorDIR = A1;
int sensorTRAS = A2;

int valorSensor = 0;
void setup() {
  SERVO.attach(0);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  float Temp, Dist;
  SERVO.write(90);
  delay(1000);
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  Temp = pulseIn(echoPin, HIGH);
  
  Dist = (Temp/2)/29.1;
  
  Serial.print(Dist);
  Serial.print("cm");
  Serial.println();
  delay(1000);
  
  valorSensor = analogRead(sensorESQ);
  
  Serial.print("Valor Sensor");
  Serial.print(valorSensor);
  Serial.println();
  delay (250);
}
