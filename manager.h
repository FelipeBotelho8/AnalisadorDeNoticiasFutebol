/* EEL670 - Linguagens de Programacao - 2018/1
   Prof.: Miguel Campista

   Trabalho 3 - Analisador de Noticias de Futebol

   Autor: Felipe Botelho Nunes da Silva
*
*/

#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include "news.h"

using namespace std;

class Manager {
   public:
      Manager();
      void setOption(unsigned);
      void executeOption();

   private:
      unsigned option;
      vector <News> newsObjs;
      PerlWrapper wrapper;

      string insertNews();
      string removeNews();
      void showAllNews();
      void showNewsInformations();
      void showTrustLevel();
      void findFileByClub();
      void findFileByNewsKind();
      void changeTeam();
      int searchNews();
      int searchNews(string &);
};


#endif
