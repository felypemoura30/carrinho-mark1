#include <IRremote.h>
#include <Servo.h>
int ENABLEA = 1;
int IN1= 2;
int IN2= 3;
int ENABLEB = 4;
int IN3 = 5;
int IN4 = 6;
Servo SERVO1;
int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode (IN1,OUTPUT);
  pinMode (IN2,OUTPUT);
  pinMode (IN3,OUTPUT);
  pinMode (IN4,OUTPUT);
  SERVO1.attach(0);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    SERVO1.write(90);
    if (results.value == 0xFF18E7){
      
  digitalWrite (ENABLEA, 10000);
  digitalWrite (ENABLEB, 10000);
  digitalWrite (IN1, LOW); //rotação pra frente
  digitalWrite (IN2, HIGH);
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  delay (2000);
    }
  }
}
