//Código para pareamento dos módulos Bluetooths

#include <SoftwareSerial.h>// Biblioteca para habilitar porta serial extra
   
//Como o arduino estará conectado ao monitor inicial para pareamento dos módulos bluetooths, é necessário criar portas seriais adicionais, 
//uma vez que o microcontrolador mestre é um Arduino Uno, a utilização da porta USB prejudica a utilização simultânea das portas seriais RX0 e TX0, 
//por seu circuito ser em série com a porta USB
SoftwareSerial Pareamento(8, 9); // RX, TX  
String Comando = ""; //Armazena resposta do módulo Bluetooth
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() //Função de configuração
{  
  Serial.begin(115200);  //Inicia a serial com o monitor serial 
  Serial.println("Digite os comandos AT :"); //Interfaceamento com o usuário
  Pareamento.begin(38400);  //Inicia a serial configurada nas portas 10 e 11
}  
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------  
void loop() //Função de iteração
{  
  if (Pareamento.available()) //Verifica se há comunicação disponível
  {  
     while(Pareamento.available())  //Enquanto houver dados para serem lidos, continuar lendo
     {  
       Comando += (char)Pareamento.read(); //Variável recebe dados de leitura
     }  
   Serial.println(Comando);  
   Comando = ""; //Esvazia a variável para evitar repetição de leitura de um mesmo dado
  }  
  
  if (Serial.available()) //Lê entrada do usuário se estiver disponível
  {  
    delay(10);
    Pareamento.write(Serial.read());
  }  
}
