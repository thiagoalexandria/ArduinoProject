/******************************************
* Autor: Thiago Alexandria
* Arduino TCC Project / Mais informações em breve
* João Pessoa - PB / 04/08/2018
* 
* Esta função irá ler os valores coletados no LDR e retornará 
* o resultado obtido por ele.
******************************************/
   
int LDR1 = 0; //Escolher porta analógica utilizada pelo LDR    
int ValLDR= 0; //Valor coletado;

void setup() {
 Serial.begin(9600); //Inicia a comunicação serial
}
 
void loop() {

 
 ValLDR = analogRead(LDR1); //O valor lido será entre 0 e 1023
 
 //imprime o valor lido do LDR no monitor serial
 Serial.println(ldrValor);
 delay(100);
}