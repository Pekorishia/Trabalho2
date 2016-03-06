/*
 * Universidade Federal do Rio Grande do Norte
 * Instituto Metropole Digital
 *
 * copyright: Ivanovitch Silva
 * e-mail: ivan@imd.ufrn.br
 *
 * Editado por: João Santana e Patricia Pontes
 * Tópico: manipulação de processos
 * Programa: usar o fork de uma maneira mais elaborada
 */

#include "../../../BlackLib/v3_0/BlackGPIO/BlackGPIO.h"
#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <time.h>
#include <string>

using namespace std;

#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////ATENÇÃO///////////////////////////////////////////////////////////
//               SEMPRE DAR O COMANDO: sudo sh -c "echo 'BB-ADC' > /sys/devices/platform/bone_capemgr/slots"


int main(int argc, char *argv[])
{

    printf("Iniciando o programa\n");

	  //variavel de tempo
    time_t rawtime;

    // Identificador do processo
    pid_t processo1;

    // Criando o processo
    processo1 = fork();

    switch(processo1){	
        case -1:       // erro
            exit(1);

        //PROCESSO 1 ----------------------------------------------------------------------------------------------    

        case 0:        // filho1
            for (int i=0;i<10;i++){
                sleep(2);

                //LIGA LED VERMELHO
                ligaLed(1);

                time (&rawtime);
                printf ("%s Filho 1 - vou ligar o LED VERMELHO", ctime (&rawtime));

                //escrever no filho_1.txt o texto acima

            }
            exit(1);

        default:    //pai
            pid_t processo2;
	          processo2 = fork();
	     
            //PROCESSO 2 ------------------------------------------------------------------------------------------

            switch(processo2){
		            case -1:       // erro
                   exit(1);
                case 0:        // filho2
                   for (int i=0;i<10;i++){
                      sleep(3);

                      //LIGA LED VERDE
                      ligaLed(2);

                      time (&rawtime);
                      printf ("%s Filho 2 - vou ligar o LED VERDE", ctime (&rawtime));

                      //escrever no filho_2.txt o texto acima
                   }
                   exit(1);
                default:
		                pid_t processo3;
		                processo3 = fork();

                    //PROCESSO 3 ----------------------------------------------------------------------------------

                    switch(processo3){
		                    case -1:       // erro
                           exit(1);
                        case 0:        // filho3
                           for (int i=0;i<10;i++){
                              sleep(4);

                              //LIGA LED AZUL
                              ligaLed(3);

                              time (&rawtime);
                              printf ("%s Filho 3 - vou ligar o LED AZUL", ctime (&rawtime));

                              //escrever no filho_3.txt o texto acima
                           }
                           exit(1);
                        default:
		                        pid_t processo4;
		                        processo4 = fork();

                            //PROCESSO 4 --------------------------------------------------------------------------

                            switch(processo4){  
                                  case -1:       // erro
                                      exit(1);
                                  case 0:        // filho4
                                     for (int i=0;i<10;i++){
                                          //printf("Sou o processo filho ID: %d\n",getpid());
                                          sleep(1);

                                          //POTENCIOMETRO   - readAnalog(1)
                                          time (&rawtime);
                                          printf ("%s Filho4 - valor do potenciometro é %d", ctime (&rawtime), readAnalog(1));

                                          //escrever no filho_4.txt o texto acima
                                      }
                                      exit(1);

                                  //PAI FINAL ---------------------------------------------------------------------    
                                  default:

                                    //fica em espera dos filhos terminarem
                                      while (true) {
                                          int status;
                                          pid_t done = wait(&status);
                                          if (done == -1) {
                                              if (errno == ECHILD){// no more child processes
                                                  
                                                  //lê todos os arquivos (filho_1, filho_2, filho_3 e filho_4) 

                                                  //ordena tudo baseado no ctime gravado nas linhas e escreve em saidas.text
                                                  //  Wed Feb 13 16:06:10 2016

                                              }
                                          } 
                                          else {
                                              if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                                                  cerr << "pid " << done << " failed" << endl;
                                                  exit(1);
                                              }
                                      }                                    
                                  exit(1);
                            }
                        exit(1);
                    }        
                exit(1);
            }  
        exit(1);            
	  }


    printf("O processo com ID: %d finalizou!!!!\n",getpid());
    return 0;
}

//retorna o valor do potenciometro
int readAnalog(int number){
   stringstream ss;
   ss << PATH_ADC << number << "_raw";
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> number;
   fs.close();
   return number;
}

//liga o led 
//1 = vermelho, 2 = verde, 3 = azul 
int ligaLed(int value){
    BlackLib::BlackGPIO   ledR(BlackLib::GPIO_60,BlackLib::output, BlackLib::SecureMode);
    BlackLib::BlackGPIO   ledG(BlackLib::GPIO_50,BlackLib::output, BlackLib::SecureMode);
    BlackLib::BlackGPIO   ledB(BlackLib::GPIO_51,BlackLib::output, BlackLib::SecureMode);
 
 
    if (value == 1){
        ledR.setValue(BlackLib::high);
        ledG.setValue(BlackLib::low);
        ledB.setValue(BlackLib::low);
        sleep(3);
        ledR.setValue(BlackLib::low);
        ledG.setValue(BlackLib::low);
        ledB.setValue(BlackLib::low);
    }
    else if (value == 2){
        ledR.setValue(BlackLib::low);
        ledG.setValue(BlackLib::high);
        ledB.setValue(BlackLib::low);
        sleep(3);
        ledR.setValue(BlackLib::low);
        ledG.setValue(BlackLib::low);
        ledB.setValue(BlackLib::low);
    }
    else if (value == 3){
        ledR.setValue(BlackLib::low);
        ledG.setValue(BlackLib::low);
        ledB.setValue(BlackLib::high);
        sleep(3);
        ledR.setValue(BlackLib::low);
        ledG.setValue(BlackLib::low);
        ledB.setValue(BlackLib::low);
    }
    else{
        ledR.setValue(BlackLib::high);
        ledG.setValue(BlackLib::high);
        ledB.setValue(BlackLib::high);
        sleep(3);
        ledR.setValue(BlackLib::low);
        ledG.setValue(BlackLib::low);
        ledB.setValue(BlackLib::low);
    }
}