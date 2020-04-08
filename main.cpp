/* EEL670 - Linguagens de Programacao - 2018/1
   Prof.: Miguel Campista

   Trabalho 3 - Analisador de Noticias de Futebol

   Autor: Felipe Botelho Nunes da Silva
*
*/

#include <iostream>
#include <string>
#include <vector>
#include "manager.h"

using namespace std;

int main() {
   double option = 0;
   unsigned auxOption;
   string any;
   Manager manager; //objeto gerenciador de noticias

   while (option != 9) {
      system("clear");
      cout << "***************************************************" << endl;
      cout << "********BEM VINDO AO ANALISADOR DE NOTICIAS********" << endl;
      cout << "***************************************************" << endl;
      cout << "\nO que deseja fazer?" << endl;
      cout << "\n1 - Inserir uma noticia." << endl;
      cout <<   "2 - Remover uma noticia." << endl;
      cout <<   "3 - Mostrar todas as noticias inseridas." << endl;
      cout <<   "4 - Mostrar informacoes sobre uma noticia." << endl;
      cout <<   "5 - Mostrar grau de confiabilidade de uma noticia." << endl;
      cout <<   "6 - Encontrar noticias sobre determinado Time." << endl;
      cout <<   "7 - Encontrar noticias sobre determiando assunto (resultado, contusao, transferencia)" << endl;
      cout <<   "8 - Trocar times." << endl;
      cout <<   "9 - Sair." << endl;

      cout << "\nEscolha uma opcao: ";
      cin >> option;
      if (cin.fail()) { //Trata a insercao de string
         cin.clear();
         cin.ignore();
         cout << "\nOpcao invalida!" << endl;
         getline(cin, any);
      }
      else {
         cin.ignore();

         auxOption = static_cast<unsigned> (option);
         if (auxOption != option) { option = 0;} //Opcao invalida (se racional ou negativo, opcao vira 0)

         manager.setOption(option);
         manager.executeOption();
      }

      if (option != 9) {
         cout << "\nAperte ENTER para continuar: ";
         getline(cin, any);
      }

   }


   return 0;
}
