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

#include "../BlackLib/v3_0/BlackGPIO/BlackGPIO.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <time.h>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////ATENÇÃO///////////////////////////////////////////////////////////
//               SEMPRE DAR O COMANDO: sudo sh -c "echo 'BB-ADC' > /sys/devices/platform/bone_capemgr/slots"

vector<string> getData(string file){
    vector<string> lines;
    while(true){
        ifstream Data(file.c_str());
        if(Data.is_open()){
            string str;
            while(!Data.eof()){
                getline(Data, str);
                lines.push_back(str);
            }
            return lines;
        }
        else{
            cout << "Seu arquivo não foi encontrado, digite um nome correto ";
            return lines;
        }
    }
}

void generateOutput(){
  vector<string> filho1 = getData("filho_1.txt");
  vector<string> filho2 = getData("filho_2.txt");
  vector<string> filho3 = getData("filho_3.txt");
  vector<string> filho4 = getData("filho_4.txt");
  vector<string> out;
  out.insert(out.end(), filho1.begin(), filho1.end());
  out.insert(out.end(), filho2.begin(), filho2.end());
  out.insert(out.end(), filho3.begin(), filho3.end());
  out.insert(out.end(), filho4.begin(), filho4.end());
  sort(out.begin(), out.end());
  ofstream saida;
  saida.open("saida.txt");
  for(unsigned int i=0; i<out.size(); i++){
    saida << out[i] << "\n";
  }
  saida.close();
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
void ligaLed(int value){
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


int main(){

    printf("Iniciando o programa\n");

      //variavel de tempo
    time_t rawtime;

    // Identificador do processo
    pid_t processo1;

    // Criando o processo
    processo1 = fork();
    int teste;
    ofstream filho1;
    ofstream filho2;
    ofstream filho3;
    ofstream filho4;

    switch(processo1){
        case -1:       // erro
            exit(1);

        //PROCESSO 1 ----------------------------------------------------------------------------------------------

        case 0:        // filho1

            filho1.open("filho_1.txt");
            for (int i=0;i<10;i++){
                sleep(2);
                //LIGA LED VERMELHO
                ligaLed(1);

                time (&rawtime);
                string temp = ctime(&rawtime);
                temp[temp.length()-1] = '\0';
                cout << temp << " Filho 1 - vou ligar o LED VERMELHO\n";

                //escrever no filho_1.txt o texto acima
                filho1 << temp << " Filho 1 - vou ligar o LED VERMELHO\n";

            }
            filho1.close();
            exit(1);

        default:    //pai
            pid_t processo2;
              processo2 = fork();

            //PROCESSO 2 ------------------------------------------------------------------------------------------

            switch(processo2){
                    case -1:       // erro
                   exit(1);
                case 0:        // filho2
                   filho1.open("filho_2.txt");
                   for (int i=0;i<10;i++){
                      sleep(3);
                      //LIGA LED VERDE
                      ligaLed(2);

                      time (&rawtime);
                      string temp = ctime(&rawtime);
                      temp[temp.length()-1] = '\0';
                      cout << temp << " Filho 2 - vou ligar o LED VERDE\n";

                      //escrever no filho_2.txt o texto acima
                      filho2 << temp << " Filho 2 - vou ligar o LED VERDE\n";

                   }
                   filho2.close();
                   exit(1);
                default:
                        pid_t processo3;
                        processo3 = fork();

                    //PROCESSO 3 ----------------------------------------------------------------------------------

                    switch(processo3){
                            case -1:       // erro
                           exit(1);
                        case 0:        // filho3
                           filho3.open("filho_3.txt");
                           for (int i=0;i<10;i++){
                              sleep(4);
                              //LIGA LED AZUL
                              ligaLed(3);

                              time(&rawtime);
                              string temp = ctime(&rawtime);
                              temp[temp.length()-1] = '\0';
                              cout << temp << " Filho 3 - vou ligar o LED AZUL\n";

                              //escrever no filho_3.txt o texto acima
                              filho3 << temp << " Filho 3 - vou ligar o LED AZUL\n";

                           }
                           filho3.close();
                           exit(1);
                        default:
                                pid_t processo4;
                                processo4 = fork();

                            //PROCESSO 4 --------------------------------------------------------------------------

                            switch(processo4){
                                  case -1:       // erro
                                      exit(1);
                                  case 0:        // filho4
                                     filho4.open("filho_4.txt");
                                     for (int i=0;i<10;i++){
                                          //printf("Sou o processo filho ID: %d\n",getpid());
                                          sleep(1);

                                          //POTENCIOMETRO   - readAnalog(1)
                                          time (&rawtime);
                                          string temp = ctime(&rawtime);
                                          temp[temp.length()-1] = '\0';
                                          cout << temp << " Filho4 - valor do potenciometro é " << readAnalog(1) << endl;

                                          //escrever no filho_4.txt o texto acima

                                          filho4 << temp << " Filho 4 - valor do potenciometro " << readAnalog(1) << endl;

                                      }
                                      filho4.close();
                                      exit(1);

                                  //PAI FINAL ---------------------------------------------------------------------
                                  default:
                                    //while(wait(null) > 0);

                                    for(int i=0; i<4; i++)
                                        wait(&teste);

                                    generateOutput();

                                    cout << "Processos terminados e arquivos salvos" << endl;

                                  exit(1);
                            }
                        exit(1);
                    }
                exit(1);
            }
        exit(1);
      }
    return 0;
}
