/* EEL670 - Linguagens de Programacao - 2018/1
   Prof.: Miguel Campista

   Trabalho 3 - Analisador de Noticias de Futebol

   Autor: Felipe Botelho Nunes da Silva
*/

#ifndef PERLWRAPPER_H
#define PERLWRAPPER_H

#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>

using namespace std;

class PerlWrapper {
   public:
      //PerlWrapper();
      PerlWrapper(string);
      ~PerlWrapper();
      //void runInterpreter(char *file);
      void runInterpreter();
      int getTrustLevel(string fileNews, string &value, string perlFunc);
      string getChangeTeam(string fileTeam, string userTeam, string perlFunc);
   private:
      PerlInterpreter *my_perl;
      char *my_argv[2];
};

#endif
