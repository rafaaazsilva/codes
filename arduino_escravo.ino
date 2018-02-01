//ARDUINO MEGA (ESCRAVO)
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
//LEDs indicadores de funcionamento
#define LED_E1 23
#define LED_E2 25
#define LED_E3 27
#define LED_E4 29
#define LED_fita1 31
#define LED_fita2 33
#define LED_lampada 35
#define LED_ON 37
#define LED_ilumina 39

//Portas acionadoras dos equipamentos de boate utilizados no modo automatico
#define E1 18
#define E2 19
#define E3 20
#define E4 21

//Portas acionadoras da iluminação residencial controladas no modo manual
#define Fita1 12
#define Fita2 11
#define Lampada 10

boolean dataComplete = false; // Status se a comunicação foi completada
boolean dataValidate = false;  // Status se os dados recebidos são válidos: status de gravação
char Char_Bus; //Variável de alocação temporária do número do pacote para passar pela filtragem de validação de dados
char Dados; //Variável que recebe dados validados usados para acionamento dos equipamentos
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600); //Inicial a comunicaçao serial conectada ao arduino mestre (painel secundario)

//Define as portas como saida
  pinMode(LED_E1, OUTPUT);
  pinMode(LED_E2, OUTPUT);
  pinMode(LED_E3, OUTPUT);
  pinMode(LED_E4, OUTPUT);
  pinMode(LED_fita1, OUTPUT);
  pinMode(LED_fita2, OUTPUT);
  pinMode(LED_lampada, OUTPUT);
  pinMode(LED_ON, OUTPUT);
  pinMode(LED_ilumina, OUTPUT);

  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(E3, OUTPUT);
  pinMode(E4, OUTPUT);

  pinMode(Fita1, OUTPUT);
  pinMode(Fita2, OUTPUT);
  pinMode(Lampada, OUTPUT);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() 
{
  LED_ON, HIGH; //Acende LED que indica que o sistema ligou
  LED_ilumina, HIGH; //Acende LED de iluminação da caixa

  if (Serial.available()) {

    while (Serial.available()) {
      Recebe();
    }
    
    if (dataComplete && !dataValidate)
    {
      dataComplete = false;
    }
  }

  switch (Dados)
  {
    case '1':
      E1, HIGH;
      LED_E1, HIGH;
      E2, HIGH;
      LED_E2, HIGH;
      E3, LOW;
      LED_E3, LOW;
      E4, LOW;
      LED_E4, LOW;
      break;
      
    case '2':
      E1, LOW;
      LED_E1, LOW;
      E2, LOW;
      LED_E2, LOW;
      E3, HIGH;
      LED_E3, HIGH;
      E4, HIGH;
      LED_E4, HIGH;
      break;
      
    case '3':
      E1, HIGH;
      LED_E1, HIGH;
      E2, LOW;
      LED_E2, LOW;
      E3, HIGH;
      LED_E3, HIGH;
      E4, LOW;
      LED_E4, LOW;
      break;

    case '4':
      E1, HIGH;
      LED_E1, HIGH;
      E2, HIGH;
      LED_E2, HIGH;
      E3, LOW;
      LED_E3, LOW;
      E4, HIGH;
      LED_E4, HIGH;
      break;

    case '5':
      E1, HIGH;
      LED_E1, HIGH;
      E2, HIGH;
      LED_E2, HIGH;
      E3, HIGH;
      LED_E3, HIGH;
      E4, HIGH;
      LED_E4, HIGH;
      break;

    case '6':
      analogWrite(Fita1, 128);
      LED_Fita1, HIGH;
      analogWrite(Fita2, 128);
      LED_Fita2, HIGH;
      Lampada, LOW;
      LED_Lampada, LOW;
      break;

    case '7':
      Fita1, LOW;
      LED_Fita1, LOW;
      Fita2, LOW;
      LED_Fita2, LOW;
      Lampada, HIGH;
      LED_Lampada, HIGH;
      break;
  }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Recebe(void)
{
  Char_Bus = (char)Serial.read(); //Lê caractere disponivel na comunicação
  
  if (Char_Bus == '+' && !dataComplete) //Protocolo de comunicação: só permite ler se o primeiro caractere for "+"
  {
    dataValidate = true;//Muda status do protocolo para permitir gravar os dados recebidos
    Dados = "";//Prepara o vetor "Dados" para ser gravado
    break;
  }
      
  if (Char_Bus == '-' && dataValidate) //Protocolo de comunicação: muda status de gravação indicando que a gravação acabou
  {
    dataValidate = false;
    dataComplete = true;
    break;
  }
  
  if (dataValidate) //Se o status de gravação for verdadeiro, então grava o dado recebido para a variável segura de operação
  { 
    Dados = Char_Bus; //Transfere o dado validado da alocação temporária (para filtragem de validação) para a variável segura que será utilizada nos acionamentos dos equipamentos
  } 
  Serial.flush();
}

