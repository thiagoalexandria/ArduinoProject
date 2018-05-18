
/********************************************************************************
* http://www.microcontroller-project.com/snmp-over-arduino-ethernet-shield.html *
* Escrito Por: Thiago Alexandria												*
* Início: 18-Maio-2018															*
*																				*
********************************************************************************/

#include <Streaming.h>
#include <Ethernet.h>
#include <SPI.h>
#include <MemoryFree.h>
#include <Agentuino.h>
#include <Flash.h>

//Configurações modulo Ethernet
static byte mac[] = { }; 	  		//Endereço MAC do arduino
static byte ip[] = {192,168,0,3};			//Endereço IP do arduino
static byte gateway[]={192,168,0,1};			//Gateway da red
static byte subnet[] = {255,255,255,0};			//Mascara de subrede



