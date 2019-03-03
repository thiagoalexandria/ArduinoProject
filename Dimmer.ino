/******************************************
* Autor: Thiago Alexandria
* Arduino TCC Project / Mais informações em breve
* João Pessoa - PB / 03/03/2019
* 
* Esta função irá ler os valores coletados no LDR e tratará esta função servirá de aṕoio para 
* o controle de energia de fluxo teremos divisões através de níveis de sensibilidade de lux.
* valores referentes aos status high, established, low poderá sofrer alteração de acordo com a
* a NBR 5413 de iluminação de interiores.
******************************************/

#define PINO_ZC 2
#define PINO_DIM 9
int LDR1 = A0;
int sensor1 = 0;

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
  sensor1 = analogRead(LDR1);
  
  if (sensor1 > 500){
    for (byte i=10; i<50; i++) {
      luminosidade=25;
     delay(15);     
    }
  }
  if (sensor1 < 500 && sensor1 > 300){
    for (byte i=10; i<50; i++) {
      luminosidade=50;
     delay(15);     
    }
  }

  if (sensor1 < 300){
    for (byte i=10; i<50; i++) {
      luminosidade=90;
     delay(15);     
    }
  }
  delay(1000);
}
