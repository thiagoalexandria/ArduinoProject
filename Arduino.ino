
/******************************************
 * Autor: Thiago Alexandria
 * Arduino TCC Project / Mais informações em breve
 * João Pessoa - PB / 10/02/2019
 * 
 ******************************************/


#include <SPI.h>
#include <Ethernet.h>
#define AGENTPING 1 //Disponivel
#define VERSION 1.0 //Versao
#define LDR 180 //Valor fixo LDR para teste
#define USO 20  //Valor fixo USO para teste


//Informacoes de endereco IP, gateway, mascara de rede
byte mac[] = { 0xA4, 0x28, 0x72, 0xCA, 0x55, 0x2F };    //MAC
byte ip[] = { 192, 168, 0, 3 };                         //IP
byte gateway[] = { 192, 168, 0, 1 };                    //IP GATEWAY
byte subnet[] = { 255, 255, 255, 0 };                   //IP MASK

EthernetServer server(10050);   //ZABBIX CLIENT PORT
EthernetClient client;          //START CLIENT
String hostname = "monitor.ino";

String opcao[] = {"monitor.ping", "monitor.hostname", "monitor.version", "monior.ldr", "monitor.uso"};


void setup() {
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}


void loop() {
  EthernetClient client = server.available();
  if (client) {
    if (client.available() > 0) {
      char thisChar = client.read();
      if (thisChar == '\n') {

        switch(findId(msg)){
          case 0:
            server.println(AGENTPING);
            break;
          case 1:
            server.println(hostname);
            break;
          case 2:
            server.println(VERSION);
            break;
          case 3:
            server.println(LDR);
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

int findId(String text) {
  int returnValue=-1;
  for (int i=0; i < OPCAO_SIZE; i++){
    if(opcao[i].equals(text)){
      returnValue = i; 
    }
  }
  return returnValue;
}