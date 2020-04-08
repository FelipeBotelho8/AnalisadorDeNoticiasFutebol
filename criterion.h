/* EEL670 - Linguagens de Programacao - 2018/1
   Prof.: Miguel Campista

   Trabalho 3 - Analisador de Noticias de Futebol

   Autor: Felipe Botelho Nunes da Silva
*
*/ 
 
#ifndef CRITERION_H
#define CRITERION_H

#include <iostream>
#include <string>

using namespace std;

class Criterion {
   public:
      Criterion(string = "Nao Identificado", unsigned = 0);
      string getValue() const;
      unsigned getTrustLevel() const;
      void setValue(string);
      void setTrustLevel(unsigned);

   private:
      string value;
      unsigned trustLevel;
};

#endif

