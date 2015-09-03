char NOME[10] = "mark2"; //muda o nome da placa bhuetooh
char BPS = '4'; // define a frequncia de bis por segundo de comunicação 1=1200, 2=2400, 3=4800, 4=9600
char PASS[10] = "1234"; //define a senha do modulo com 4 digitos

void setup(){
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  delay(10000);
  digitalWrite(13,LOW);
  
  Serial.print("AT");             //inicia a configuração do modulo 
  delay(1000);
  
  Serial.println("AT+NAME");        //inicia a configuração do nome
  Serial.println(NOME);
  delay(1000);
  
  Serial.println("AT+BAUND");      //inicia a configuração da taxa de bit por segundo
  Serial.println(BPS);
  delay(1000);
  
  Serial.println("AT+PIN");         //inicia a configuração da senha
  Serial.println(PASS);
  delay(1000);
  
}

void loop(){
  digitalWrite(13, !digitalRead(13));
  delay(500);
}
