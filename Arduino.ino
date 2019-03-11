/******************************************
* Autor: Thiago Alexandria
* Arduino TCC Project / Mais informações em breve
* João Pessoa - PB / 03/03/2019
* 
******************************************/

#include <Ethernet.h>
#include <SPI.h>

//Declaração para interface Ethernet e porta de comunicação
#define MACADDRESS 0xA4, 0x28, 0x72, 0xCA, 0x55, 0x2F 
#define IP 192,168,0,3
#define LISTENPORT 10050

//VARIÁVEIS GLOBAIS
#define USO 15                // Valor fixo para uso em %
#define ZABBIXPING 1          //Resposta Ping 
#define ZABBIXPROTOCOL 3.4    //Versão do protocolo 3.4
#define ITEMS_SIZE  7         //TAMANHO MÁXIMO DA LSITA DE ITENS
#define PINO_ZC 2             //Pino Zecros
#define PINO_DIM 9            //Pino Dimmer

//COMANDOS ACEITOS
String items[] = { "agent.ping", "agent.hostname", "agent.version", "agent.ldr", "agent.uso" };

//HOSTNAME DO DISPOSITIVO
String hostname = "tcc-monitor";

//SENSORES
int LDR1 = A0; int LDR2 = A1; int LDR3 = A2; int LDR4 = A3

//OUTRAS VARIÁVEIS
int state_ldr1 = 0; int state_ldr2 = 0;
int state_ldr3 = 0; int state_ldr4 = 0;
int state_media = 0; String msg ="";

//INICIANDO O SERVER NA PORTA 10050
EthernetServer server = EthernetServer(LISTENPORT);

//SETUP, INICIANDO O DISPOSITIVO
void setup() {
  //NETWORK
  uint8_t mac[6] = {MACADDRESS};
  uint8_t ip[4] = {IP};
  delay(1000);
  Ethernet.begin(mac,ip);
  server.begin();
  pinMode(PINO_DIM, OUTPUT);
  attachInterrupt(0, zeroCross, RISING);
}

//LOOP COM O SWITCH CASE RESPONSÁVEL POR RECEBER
//O COMANDO E INFORMAR O QUE DEVE SER RETORNADO
void loop() {
  EthernetClient client = server.available();
  if (client) {
    if (client.available() > 0) {
      char thisChar = client.read();
      if (thisChar == '\n') {

        switch(findId(msg)){
          case 0:
            server.println(ZABBIXPING);
            break;
          case 1:
            server.println(hostname);
            break;
          case 2:
            server.println(ZABBIXPROTOCOL);
            break;
          case 3:
            server.println(ldrLer(state_ldr1,state_ldr2,state_ldr3,state_ldr4));
            break;
          case 4:
            server.println();
            break;
          default:
            server.println("ZBX_NOTSUPPORTED");
        }

        client.stop();
        msg="";
      }else {
        msg += thisChar;  
      }
    }
  }
}

//FUNÇÃO PARA TRATAR O COMANDO RECEBIDO E BUSCAR
//NA LISTA DE COMANDOS A SUA POSIÇÃO NA LISTA

int findId(String text) {
  int returnValue=-1;
  for (int i=0; i < ITEMS_SIZE; i++){
    if(items[i].equals(text)){
      returnValue = i; 
    }
  }
  return returnValue;
}

//FUNÇÃO PARA LEITURA E RETORNO DA MÉDIA DOS LDRS
int ldrLer(int state_ldr1, int state_ldr2, int state_ldr3, int state_ldr4){

   state_ldr1 = analogRead(LDR1);
   state_ldr2 = analogRead(LDR2);
   state_ldr3 = analogRead(LDR3);
   state_ldr4 = analogRead(LDR4);

   state_media=(state_ldr1+state_ldr2+state_ldr3+state_ldr4)/4;
   return state_media;
}

void zeroCross()  {
  if (luminosidade>100) luminosidade=100;
  if (luminosidade<0) luminosidade=0;
  long t1 = 8200L * (100L - luminosidade) / 100L;      
  delayMicroseconds(t1);   
  digitalWrite(PINO_DIM, HIGH);  
  delayMicroseconds(6);      // t2
  digitalWrite(PINO_DIM, LOW);   
}
