/******************************************
 * Autor: Thiago Alexandria
 * Arduino TCC Project / Mais informações em breve
 * João Pessoa - PB / 18/05/2018
 * 
 ******************************************/


#include <SPI.h>
#include <Ethernet.h>

//Informacoes de endereco IP, gateway, mascara de rede
byte mac[] = { 0xA4, 0x28, 0x72, 0xCA, 0x55, 0x2F };
byte ip[] = { 192, 168, 0, 3 };
byte gateway[] = { 192, 168, 0, 1 };
byte subnet[] = { 255, 255, 255, 0 };

EthernetServer server(80);

void setup()
{

  //Inicializa Ethernet Shield
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();

  

  //Desliga os dois reles
}
  
void loop()
{
  
}
