
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
static byte mac[] = {}; 			//Endereço MAC do arduino
static byte ip[] = {};				//Endereço IP do arduino
static byte gateway[]={};			//Gateway da red
static byte subnet[] = {};			//Mascara de subrede



