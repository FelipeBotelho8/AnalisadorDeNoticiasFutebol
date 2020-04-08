/* EEL670 - Linguagens de Programacao - 2018/1
   Prof.: Miguel Campista

   Trabalho 3 - Analisador de Noticias de Futebol

   Autor: Felipe Botelho Nunes da Silva
*
*/

#ifndef NEWS_H
#define NEWS_H

#include <iostream>
#include <string>
#include "criterion.h"
#include "perlWrapper.h"

using namespace std;

class News {
   public:
      News(string);
      string getFileName();
      string getTrustKind();
      unsigned getTotalTrustLevel();
      Criterion &getAuthor();   
      Criterion &getClub();  
      Criterion &getDate();  
      Criterion &getNewsKind();  
      Criterion &getPress();
      void analyzeNews(PerlWrapper &);
      void setTotalTrustLevel();

   private:
      string fileName;
      string trustKind; //confiavel, insegura ou falsa
      unsigned totalTrustLevel; //confiabilidade - em porcentagemset
      Criterion author;
      Criterion club;
      Criterion date; 
      Criterion newsKind;
      Criterion press;
      
      void setTrustKind();
};

#endif 
