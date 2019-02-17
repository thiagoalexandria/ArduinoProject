
/******************************************
 * Autor: Thiago Alexandria
 * Arduino TCC Project / 
 * João Pessoa - PB / 16/02/2019
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

//VARIÁVEIS NÃO GLOBAIS
//COMANDOS ACEITOS
String items[] = { "agent.ping", "agent.hostname", "agent.version", "agent.ldr", "agent.uso" };
//HOSTNAME DO DISPOSITIVO
String hostname = "tcc-monitor";
//SENSORES
int LDR1 = A0; int LDR2 = A1;
//OUTRAS VARIÁVEIS
int sensor1 = 0; int sensor2 = 0; int MEDIA = 0; String msg ="";

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
            server.println(ldrLer(sensor1,sensor2));
            break;
          case 4:
            server.println(USO);
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
int ldrLer(int sensor1, int sensor2){
   sensor1 = analogRead(LDR1);
   sensor2 = analogRead(LDR2);
   MEDIA=(sensor1+sensor2)/2;
   return MEDIA;
}

