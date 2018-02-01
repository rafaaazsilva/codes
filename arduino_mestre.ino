//ARDUINO UNO (MESTRE)
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* PACOTES DE ACIONAMENTO:
 *  
 *   1) MODO AUTOMÁTICO (E1, E2, E3, E4)
 *   
 *     PACOTE 1:
 *               E1: ON
 *               E2: ON
 *               E3: OFF
 *               E4: OFF
 *               
 *     PACOTE 2:
 *               E1: OFF
 *               E2: OFF
 *               E3: ON
 *               E4: ON
 *               
 *     PACOTE 3:
 *               E1: ON
 *               E2: OFF
 *               E3: ON
 *               E4: OFF
 *               
 *     PACOTE 4:
 *               E1: ON
 *               E2: ON
 *               E3: OFF
 *               E4: ON
 *               
 *     PACOTE 5:
 *               E1: ON
 *               E2: ON
 *               E3: ON
 *               E4: ON
 *               
 *   2) MODO CINEMA
 *   
 *     PACOTE 6:
 *               Fita1: ON 30%
 *               Fita2: ON 30%
 *               Lampada: OFF
 *               
 *   2) MODO LEITURA
 *               
 *     PACOTE 7:
 *               Fita1: OFF
 *               Fita2: OFF
 *               Lampada: ON
 */
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <SoftwareSerial.h>// Biblioteca para habilitar porta serial extra

//Usou-se define ao invés de atribuiçoes (int, etc) para diminuir uso de memória
//Definicao pinos de entrada de dados do sensor
#define Sensor_Som_Analogico A0
#define Sensor_Som_Analogico 7

//Definiçao pinos de entrada para receber o modo de funcionamento
#define Modo_Festa(Automatico) 12 //Modo automatico (sensor de intensidade sonora)
//Modos manuais
#define Modo_Cinema 11
#define Modo_Leitura 10

//Variaveis para leitura dos dados do sensor de intensidade sonora
int intensidade_som = 0;
int valor_D = 0;

char Dados; //Variavel para transmissao do pacote de acionamento selecionado via comunicaçao serial
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() //Função de configuração
{
  Serial.begin(9600);
  
  //Define pinos led como saida
  pinMode(Modo_Festa(Automatico), INPUT);
  pinMode(Modo_Cinema, INPUT);
  pinMode(Modo_Leitura, INPUT);
  
  //Define pinos sensor como entrada
  pinMode(Sensor_Som_Analogico, INPUT);
  pinMode(Sensor_Som_Digital, INPUT);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop()  //Função de iteração
{
  //Se o usuário acionar o modo automático, entra na parte de controle através do sensor de intensidade sonora
  //Cada acionamento só é feito caso esteja acionado apenas aquele botão específico de modo de acionamento. Se houver 2 botões de modo acionados, o código não realiza a atuação
  if (Modo_Festa(Automatico) == HIGH && Modo_Cinema == LOW && Modo_Leitura == LOW)
  {  
    //Lê dados de entrada enviados pelo sensor de intensidade sonora
    intensidade_som = analogRead(pino_analogico);
    valor_D = digitalRead(pino_digital);

  //Determina pacote de acionamento com base nas faixas da medição analógica de intensidade sonora feita pelo sensor determinadas abaixo:
  //break evita comparações desnecessárias e retorna ao começo para uma nova iteração, economizando tempo de processamento 
    if (intensidade_som > 20 && intensidade_som <= 200) 
    {
      Dados = 1;
      Envia();
      break;
    }
  
    if (intensidade_som > 200 && intensidade_som <= 400) 
    {
      Dados = 2;
      Envia();
      break;
    }
  
    if (intensidade_som > 400 && intensidade_som <= 600) 
    {
      Dados = 3;
      Envia();
      break;
    }
    
    if (intensidade_som > 600 && intensidade_som <= 800) 
    {
      Dados = 4;
      Envia();
      break;
    }
    
    if (intensidade_som > 800) 
    {
      Dados = 5;
      Envia();
      break;
    }
  }

  if (Modo_Cinema == HIGH && Modo_Festa(Automatico) == LOW && Modo_Leitura == LOW) //
  {
    Dados = 6;
    Envia();
    break;
  }

  if (Modo_Leitura == HIGH && Modo_Cinema == LOW && Modo_Festa(Automatico) == LOW) 
  {
    Dados = 7;
    Envia();
    break;
  }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Envia(void) { //Função que envia dados processados para o arduino escravo via comunicação serial
  
  Serial.print("+"); //Protocolo de comunicação para indicar início válido de uma transmissão e leitura de dados
  Serial.print(Dados); //Envia o pacote de acionamento
  Serial.print("-"); //Protocolo de comunicação para indicar conclusão da transmissão e leitura de dados
  Dados = ""; //Esvazia varíavel de transmissão para prepará-la para receber um novo valor
}
  
