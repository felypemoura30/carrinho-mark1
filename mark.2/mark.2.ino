#include <Servo.h>  //INCLUSAO DA BIBLIOTECA DO SERVO MOTOR
#include "IRremote.h"  //INCLUSAO DA BIBLIOTECA DO CONTROLE IR
#define echoPin 12
//CONFIGURAÇÃO DOS MOTORES A/B
int ENABLEA = 1; //INICIALIZAÇÃO DO MOTOR A
int MOTORA1 = 2;     
int MOTORA2 = 3;     
int ENABLEB = 4;  //INICIALIZAÇÃO DO MOTOR B
int MOTORB1 = 5;
int MOTORB2 = 6;
//CONFIGURAÇÃO DO ULTRASSONICO
int trigger = 27;  //DEFINIÇÃO DO PINO DE TRIGGER ULTASSONICO
int echo= 12;  //DEFINIÇÃO DO PINO ECHO ULTRASSONICO

int estado = 'g'; //estado do bluetooth

int leftscanval, centerscanval, rightscanval, ldiagonalscanval, rdiagonalscanval;
char choice;

//CONFIGURAÇÃO DO CONTROLE IR
int receptor = 11; //DEFINIÇÃO DO PINO DIGITAL DO RECEPTOR IR
IRrecv irrecv(receptor); //INSTANCIA 'irrecv'
decode_results results;
char contcommand;
int modecontrol = 0;
int power = 0;

//PARAMETROS LIMITES DE DISTANCIA
int distancelimit =1;
int sidedistancelimit=12;

int distance;
int numcycles = 0;
char turndirection; //MUDA A DIREÇÃO PARA O LADO SEM OBSTACULOS;
int turntime = 900; //TEMPO PARA O CARRINHO VIRAR EM MILESEGUNDOS;
int thereis;
//INICIALIZAÇÃO DO SERVO
Servo head;
void setup() {
  head.attach(0);
  head.write(90);
  irrecv.enableIRIn();  //INICIA O SENSOR IR
  pinMode(MOTORA1, OUTPUT);  
  pinMode(MOTORA2, OUTPUT);
  pinMode(MOTORB1, OUTPUT);  //DEFINE AS PORTAS DOS MOTORES COMO SAIDAS
  pinMode(MOTORB2, OUTPUT);
  
  pinMode(trigger, OUTPUT);  //DEFINE 'trigger' DO ULTRASSONICO COMO SAIDA
  pinMode(echo, INPUT);  //DEFINE 'echo' DO ULTRASSONICO COMO ENTRADA
  
  //INICIANDO OS MOTORES
  digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, LOW);
}

void go(){
  digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, HIGH);
  digitalWrite(MOTORB1, HIGH);
  digitalWrite(MOTORB2, LOW);
}

void backwards(){
  digitalWrite(MOTORA1, HIGH);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, HIGH);
}

int watch(){
  long howfar;
  float Temp;
  digitalWrite(trigger, LOW);
  delay(5);
  digitalWrite(trigger, HIGH);
  delay (15);
  digitalWrite(trigger, LOW);
  //howfar = pulseIn(echo, HIGH);
  Temp = pulseIn(echoPin, HIGH);
  /*howfar = (Temp/2)/29.1;
  howfar = howfar * 0.5;*/
  howfar= howfar*0.01657; //'howfar' E A DISTANCIA DO OBJETO EM CM
  return round(howfar);  
}

void turnright(int t){
  digitalWrite(MOTORA1, HIGH);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, HIGH);
  digitalWrite(MOTORB2, LOW);
  delay(t);
}

void turnleft(int t){
  
  digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, HIGH);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, HIGH);
  delay(t);
  
}
void stopmove(){
  digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, LOW);
}
 void bluetooth(){ 
  
 // if(Serial.available()>0){        // LE E ARMAZENA O ESTADO DO BLUETOOH
      estado = Serial.read();
  //}
  if(estado=='a'){           // BOTAO FRENTE
  go();       
  }
  if(estado=='b'){          // BOTAO ESQUERDA 
      digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, HIGH);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, HIGH);     
  }
  if(estado=='c'){         // BOTAO PARAR
      digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, LOW);
  }
  if(estado=='d'){          // BOTAO PARA A DIREITA
       digitalWrite(MOTORA1, HIGH);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, HIGH);
  digitalWrite(MOTORB2, LOW);  
  } 
  
  if(estado=='e'){          //BOTAO DE RE 
  digitalWrite(MOTORA1, HIGH);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, HIGH);      
  }
  if (estado =='f'){          // BOTAO LIGAR 
 
  }
  if  (estado=='g'){          // BOTAO DESLIGAR 
  }
 }
void watchsurrounding(){
  centerscanval = watch();
  if(centerscanval>distancelimit){
    stopmove();
  }
  /*head.write(120);
  delay(100);
  ldiagonalscanval = watch();
  if(ldiagonalscanval>distancelimit){
      stopmove();
  }
  head.write(160);
  delay(100);
  leftscanval = watch();
  if(leftscanval>sidedistancelimit){
    stopmove();
  }
  head.write(120);
  delay(100);
  ldiagonalscanval = watch();
  if(ldiagonalscanval>distancelimit){
    stopmove();
  }
  head.write(90);
  delay(100);
  centerscanval = watch();
  if(centerscanval>distancelimit){
    stopmove();
  }
  head.write(40);
  delay(100);
  rdiagonalscanval = watch();
  if(rdiagonalscanval>distancelimit){
    stopmove();*/
  head.write(180);
  delay(900);
  rdiagonalscanval = watch();
  if(rdiagonalscanval>distancelimit){
    stopmove();
  }
  head.write(90);
  delay(900);
  rightscanval = watch();
  if(rightscanval>sidedistancelimit){ 
    stopmove();
  }
  head.write(0);
  delay(900);
  ldiagonalscanval = watch();
  if(ldiagonalscanval>distancelimit){
    stopmove();
  }
  head.write(90);
  delay(50);  
}

char decide(){
  watchsurrounding();
  if(leftscanval>rightscanval && leftscanval>centerscanval){
    choice ='l';
  }
  else if(rightscanval>leftscanval && rightscanval>centerscanval){
    choice = 'r';
  }
  else{
    choice = 'f';
  }
  return choice;
}

void translateIR(){
  switch(results.value){
    case 0xFF18E7:  //MOVE PARA FRENTE PRESSIONANDO 2
      go();
      break;
    case 0xFF10EF:  //MOVE PARA ESQUERDA PRESSIONANDO 4
      turnleft(turntime);
      stopmove();
      break;
    case 0xFF6897:  //BOTAO DE 'OK' PRESSIONANDO 0
      stopmove();
      break;
    case 0xFF5AA5:  //MOVE PARA A DIREITA PRESSIONANDO 6
      turnright(turntime);
      stopmove();
      break;
    case 0xFF4AB5:  //MOVE PARA TRAS PRESSIONANDO 8
      backwards();
      break;
    case 0xFF629D:  //MUDA O MODO DE OPERAÇÃO PRESSIONANDO MODE
      modecontrol = 0; 
      stopmove();
    case 0xFFE21D:
      modecontrol = 2;  //MUDA O MODO DE OPERAÇÃO PRESSIONANDO MUTE
      stopmove();
      break;
      default:
      ;
  }
  delay(500);  //nao fazer repetiçoes imediatas
}

void loop(){
  if(irrecv.decode(&results)){ //CHECAGEM PARA VER SE O CONTROLE IR ESTA MANDANDO SINAL
    if(results.value == 0xFF22DD ){  //LIGA O CARRINHO APERTANDO PLAY/PAUSE
      power = 1;
    }
    if(results.value == 0xFFFFA25D){ //DESLIGA O CARRINHO APERTANDO O BOTAO POWER
      stopmove();
      power = 0;
    }
    if(results.value == 0xFFE21D){
      modecontrol = 2;
      stopmove();
    }
    if(results.value == 0xFF629D){  //MUDA O MODO DE OPERAÇÃO PRESSIONANDO MODE
      modecontrol = 1; //ATIVA O MODO DE CONTROLE IR
      stopmove();  //O CARRINHO PARA E COMEÇA A RESPONDER AO CONTROLE IR    
    }
    irrecv.resume();  //RECEBE O PROXIMO VALOR 
  }
  while(modecontrol == 1){//O SISTEMA ENTRARA EM LOOP DURANTE O CONTROLE POR IR ATE 'modecontrol = 0' (APERTANDO BOTAO MODE)
      if (irrecv.decode(&results)){  // SE ALGUMA COISA FOR RECEBIDA
        translateIR();  // FAÇA ALGO DEPEDENDO DO VALOR RECEBIDO
        irrecv.resume();  // RECEBA O PROXIMO VALOR
      }
  }
  
    if(irrecv.decode(&results)){
    bluetooth();
    irrecv.resume();}
  
  if(power == 1){
    go();  // SE NAO HOUVER NADA DE ERRADO O CARRINHO IRA ANDAR PARA FRENTE
    ++numcycles;
    if(numcycles>10){  // PROCURA OBSTACULOS A CADA CICLO DE 10 LOOPS
      watchsurrounding();
      if(leftscanval<sidedistancelimit || ldiagonalscanval<distancelimit){
        turnright(turntime);
      }
      if(rightscanval<sidedistancelimit || rdiagonalscanval<distancelimit){
        turnleft(turntime);
      }
      numcycles = 0; //RE STARTA A CONTAGEM DE CICLOS
    }
    distance = watch(); //USA A FUNÇÃO 'watch();' PARA VER SE NAO A OBSTACULOS A FRENTE
    if(distance<distancelimit){ //O CARRINHO SO IRA PARAR SE REALMENTE HOUVER UM GRANDE OBSTACULO A FRENTE
      ++thereis;
    }
    if (distance>distancelimit){
      thereis=0;} //CONTAGEM E REINICIADA
    if (thereis > 25){
    stopmove(); // DESDE QUE HAJA ALGO NA FRENTE O CARRINHO PARA
    turndirection = decide(); //DECIDE QUAL DIREÇÃO VIRAR.
    switch (turndirection){
      case 'l':
        turnleft(turntime);
        break;
      case 'r':
        turnright(turntime);
        break;
      case 'f':
        ; //NAO VIRA SE NAO HOUVER NADA NA FRENTE
        break;
    }
    thereis=0;
  }
 }

}

