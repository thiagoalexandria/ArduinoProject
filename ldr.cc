/******************************************
* Autor: Thiago Alexandria
* Arduino TCC Project / Mais informações em breve
* João Pessoa - PB / 04/08/2018
* 
* Esta função irá ler os valores coletados nos
* sensores LDR e retornará a media de iluminação
* obtida entre eles, exibindo o resultado em res-
* posta serial.
******************************************/
   
int LDR1 = A0; 
int LDR2 = A1;
int LDR3 = A2;

int sensor1 = 0;
int sensor2 = 0;
int sensor3 = 0;
int media=0;

void setup() {
  Serial.begin(9600); //Inicia a comunicação serial
}

void loop() {
 sensor1 = analogRead(LDR1);
 sensor2 = analogRead(LDR2);
 sensor3 = analogRead(LDR3);
 
 media=(sensor1+sensor2+sensor3)/3;
 Serial.print("Media dos sensores:");
 Serial.println(media); 
 delay(5000);
}
