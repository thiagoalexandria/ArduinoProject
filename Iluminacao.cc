/******************************************
* Autor: Thiago Alexandria
* Arduino TCC Project / Mais informações em breve
* João Pessoa - PB / 05/07/2018
* 
* Esta função irá ler os valores coletados no LDR e tratará esta função servirá de aṕoio para 
* o controle de energia de fluxo teremos divisões através de níveis de sensibilidade de lux.
* valores referentes aos status high, established, low poderá sofrer alteração de acordo com a
* a NBR 5413 de iluminação de interiores.
******************************************/
   
int LDR1 = ?; //Escolher porta analógica utilizada pelo LDR   
int LDR2 = ?; //Escolher porta analógica utilizada pelo LDR   
int LDR3 = ?; //Escolher porta analógica utilizada pelo LDR   
int LDR4 = ?; //Escolher porta analógica utilizada pelo LDR   

   
void iluminacao()  
{  

  int state_ldr1 = analogRead(portaLDR1);  //Lê o valor fornecido pelo LDR 1 
  int state_ldr2 = analogRead(portaLDR2);  //Lê o valor fornecido pelo LDR 2
  int state_ldr3 = analogRead(portaLDR3);  //Lê o valor fornecido pelo LDR 3
  int state_ldr4 = analogRead(portaLDR4);  //Lê o valor fornecido pelo LDR 4

  int state_med = ((state_ldr1 + state_ldr2 + state_ldr3 + state_ldr4) /4); 

  if (state_med > 800) //Muito Alto    
  {  
        int high = state_med;
        return state_med;
  }
  else if (state_med < 500  && state_med > 300) //Normal
  {
        int established = state_med;
        return state_med;
  }
  else (state_med <= 300) //Low
  {
        int low = state_med;
        return state_med;
  }

}  
