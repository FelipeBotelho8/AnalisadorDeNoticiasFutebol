/* EEL670 - Linguagens de Programacao - 2018/1
   Prof.: Miguel Campista

   Trabalho 3 - Analisador de Noticias de Futebol

   Autor: Felipe Botelho Nunes da Silva
*
*/ 

#include "criterion.h"

Criterion::Criterion(string str, unsigned num) {
   setValue(str);
   setTrustLevel(num);
}

string Criterion::getValue() const {
   return value;
}

unsigned Criterion::getTrustLevel() const {
   return trustLevel;
}

void Criterion::setValue(string str) {
   value = str;
}

void Criterion::setTrustLevel(unsigned num) {
   if (num < 0) {
      trustLevel = 0; //Se num for negativo, trustLevel recebe 0
   }
   else {
      trustLevel = num;
   }
}
