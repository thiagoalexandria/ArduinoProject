
/******************************************
 * Autor: Thiago Alexandria
 * Arduino TCC Project / Mais informações em breve
 * João Pessoa - PB / 18/05/2018
 * 
 ******************************************/


#include <SPI.h>
#include <Ethernet.h>


//Informacoes de endereco IP, gateway, mascara de rede
byte mac[] = { 0xA4, 0x28, 0x72, 0xCA, 0x55, 0x2F };    //MAC
byte ip[] = { 192, 168, 0, 3 };                         //IP
byte gateway[] = { 192, 168, 0, 1 };                    //IP GATEWAY
byte subnet[] = { 255, 255, 255, 0 };                   //IP MASK

#define MAX_CMD_LENGTH 25      //MAX COMAND LENGTH
#define LED_PIN 3              // LED pin with 1k resistor
#define PIR_PIN 6              //PIR PIN

EthernetServer server(10050);   //ZABBIX CLIENT PORT
EthernetClient client;          //START CLIENT

String cmd;                     //ZABBIX COMAND
int counter = 1;                //COUNTER FOR COMANDS
int limite = 1;                 //COMAND SIZE
boolean connected = false;      //CONNECTED OR NOT
unsigned long pirLastCheck = 0; //LASTCHECK ON PIR PIN
int presence = 0;               //OBSERVE PRESENCE
int lastPresence = 0;           //AFW RECORD
int pirWaitTime = 20000;       //LONG WAIT AFK

void IniciaNet() 
{

  //Inicializa Ethernet Shield
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}

void readTelnetCommand(char c) {
  if (cmd.length() == MAX_CMD_LENGTH) {
    cmd = "";
  }
  cmd += c;
  if (c == '\n' || cmd.length() == limite) {
    parseCommand();
  }
  else {
  }
}

void readPresence() {
  if (digitalRead(PIR_PIN)) {
    pirLastCheck = millis();
    lastPresence = 1;
  }
  if (digitalRead(PIR_PIN) && (lastPresence)) {
    presence = 1;
  }
  else {
    if (millis() - pirLastCheck > pirWaitTime) {
      presence = 0;
      lastPresence = 0;
    }
  }
}


//Command on listening port 10050 
void parseCommand() {
  if (cmd.equals("")) {  }
  else {
    counter = counter + 1;
    Serial.print(" Tempo: ");
    Serial.print(millis() / 1000);
    Serial.print("\t");
    Serial.print("Cmd: ");
    Serial.print(cmd);
    Serial.print("\t\t");
    Serial.print("Resposta: ");
    
    // Teste ping 1/0
    if (cmd.equals("p")) {
      server.println("1");
    }
    
    // Versão do Agente
    else if (cmd.equals("v")) {
      server.println("Arduino beta Agent 1.0");
      delay(100);
    }
    
    // Valores dos LDRs
    else if (cmd.equals("l")) {
      
    }
    
    // Agent error
    else { 
      server.print("ZBXDZBX_NOTSUPPORTED");
    }
    cmd = "";
    Serial.println("");
    client.stop();
    }
}
  
void loop() {
  client = server.available();
  if (client) {
    if (!connected) {
      Serial.println("Conection not available");
      client.flush();
      connected = true;
      client.stop();
    }
    if (client.available() > 0) {
      Serial.println("Client Available");
      Serial.println("Conection ok");
      int clientread = client.read();
      Serial.print(clientread);
      char charcr = clientread;
      digitalWrite(LED_PIN, HIGH);
      readTelnetCommand(clientread);
      digitalWrite(LED_PIN, LOW);
    }
  }
  if (millis()%2) {
    readPresence();
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  //Serial.begin(115200);
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.println("Setup");
  delay(1000);
}
