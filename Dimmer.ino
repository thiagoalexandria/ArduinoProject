/******************************************
* Autor: Thiago Alexandria
* Arduino TCC Project / Mais informações em breve
* João Pessoa - PB / 03/03/2019
* 
* Esta função será aplicada a placa Slave do projeto, essa placa será responsável 
* por realizar a leitura constante dos valores obtidos através dos LDRS. Baseado 
* na média de Lux obtidos a placa encaminhará os valores para o módulo dimmer rea- 
* lizando a dimerização das lampadas de  acordo com a NBR 5413 de iluminação de 
* interiores, encaminhando os dados de energia para a placa Master através de uma
* comunicação serial. 

******************************************/

#define PINO_ZC 2
#define PINO_DIM 9
int LDR1 = A0; int LDR2 = A1; int LDR3 = A2; int LDR4 = A3;

//OUTRAS VARIÁVEIS
int state_ldr1 = 0; int state_ldr2 = 0;
int state_ldr3 = 0; int state_ldr4 = 0;
int state_media = 0;
volatile long luminosidade = 0;  // 0 a 100 
 
void zeroCross()  {
  if (luminosidade>100) luminosidade=100;
  if (luminosidade<0) luminosidade=0;
  long t1 = 8200L * (100L - luminosidade) / 100L;      
  delayMicroseconds(t1);   
  digitalWrite(PINO_DIM, HIGH);  
  delayMicroseconds(6);      // t2
  digitalWrite(PINO_DIM, LOW);   
}
 
void setup() {
  pinMode(PINO_DIM, OUTPUT);
  attachInterrupt(0, zeroCross, RISING);
}
 
void loop() {

  state_ldr1 = analogRead(LDR1);
  state_ldr2 = analogRead(LDR2);
  state_ldr3 = analogRead(LDR3);
  state_ldr4 = analogRead(LDR4);

  state_media=(state_ldr1+state_ldr2+state_ldr3+state_ldr4)/4;

 if (state_media > 500){
    for (byte i=10; i<50; i++) {
      luminosidade=25;
      Serial.write(25);
      delay(15);     
    }
  }
  
  if (state_media < 500 && state_media > 300){
    for (byte i=10; i<50; i++) {
      luminosidade=50;
      Serial.write(50);
     delay(15);     
    }
  }

  if (state_media < 300){
    for (byte i=10; i<50; i++) {
      luminosidade=90;
      Serial.write(90);
     delay(15);     
    }
  }
  delay(1000);
}
