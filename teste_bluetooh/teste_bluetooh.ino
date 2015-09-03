/* Carro Inalambrico Bluetooth
Dibujo de las conexiones en www.elprofegarcia.com

ARDUINO   L293D(Puente H)        
  5          10
  6          15
  9          7
  10         2
  5V         1, 9, 16
  GND        4, 5, 12, 13
  
  El motor 1 se conecta a los pines 3 y 6 del Puente H
  El motor 2 se conecta a los pines 11 y 14 del Puente H
  
  La fuente de alimentacion de los Motores se conecta a tierra y
  el positivo al pin 8 del puennte H. 
 
Conexion del Modulo Bluetooth HC-06 y el Arduino
ARDUINO    Bluetooth HC-06 
 0 (RX)       TX
 1 (TX)       RX
 5V           VCC
 GND          GND
!!Cuidado!! Las conexiones de TX y RX al modulo Bluetooth deben estar desconectadas
en el momento que se realiza la carga del codigo (Sketch) al Arduino.

*/
#include <Servo.h>
int ENABLEA = 1; //INICIALIZAÇÃO DO MOTOR A
int MOTORA1 = 2;     
int MOTORA2 = 3;     
int ENABLEB = 4;  //INICIALIZAÇÃO DO MOTOR B
int MOTORB1 = 5;
int MOTORB2 = 6;

int estado = 'g';         
Servo teste;

void setup()  { 
  teste.attach(7);
  teste.write(90);
  Serial.begin(9600);    
  pinMode(MOTORA1, OUTPUT);  
  pinMode(MOTORA2, OUTPUT);
  pinMode(MOTORB1, OUTPUT);  
  pinMode(MOTORB2, OUTPUT);
  
  digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, LOW);
 } 
 
void loop()  { 
  
  
  if(Serial.available()>0){       
      estado = Serial.read();
  }
  if(estado=='a'){           
  digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, HIGH);
  digitalWrite(MOTORB1, HIGH);
  digitalWrite(MOTORB2, LOW);       
  }
  if(estado=='b'){          
      digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, HIGH);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, HIGH);     
  }
  if(estado=='c'){         
      digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, LOW);
  }
  if(estado=='d'){          
       digitalWrite(MOTORA1, HIGH);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, HIGH);
  digitalWrite(MOTORB2, LOW);  
  } 
  
  if(estado=='e'){          
  digitalWrite(MOTORA1, HIGH);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, HIGH);      
  }
  if (estado =='f'){          
  teste.write(0);
  
  
}
  if  (estado=='g'){     
teste.write(90);
  
  
}
if (estado == 'h'){
teste.write(180);
  
  
}
}
