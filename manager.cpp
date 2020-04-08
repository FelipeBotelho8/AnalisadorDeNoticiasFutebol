/* EEL670 - Linguagens de Programacao - 2018/1
   Prof.: Miguel Campista

   Trabalho 3 - Analisador de Noticias de Futebol

   Autor: Felipe Botelho Nunes da Silva
*
*/

#include "manager.h"

Manager::Manager() : option(0), wrapper("") {
   wrapper.runInterpreter();
}

//Construtor
void Manager::setOption(unsigned num) {
   option = num;
}

//Exeuta a funcao correspondente a opcao
void Manager::executeOption() {
   string mensage;
   switch (option) {
      case 1: 
         mensage = insertNews();
         cout << mensage << endl;
         break;
      case 2: 
         mensage = removeNews();
         cout << mensage << endl;
         break;
      case 3:
         showAllNews();
         break;
      case 4:
         showNewsInformations();
         break;
      case 5:
         showTrustLevel();
         break;
      case 6:
         findFileByClub();
         break;
      case 7:
         findFileByNewsKind();
         break;
      case 8:
         changeTeam();        
         break;
      case 9:
         cout << "Saindo..." << endl;
         break;
      default:
         cout << "\nOpcao invalida!" << endl;
   }
}

//Insere uma noticia no vector
string Manager::insertNews() {
   string name;
   int index = searchNews(name);

   if(index >= 0) {return "\nNoticia ja inserida!";}
   if(index == -2) {return "\nArquivo nao encontrado!";}

   News news(name);
   news.analyzeNews(wrapper);

   newsObjs.push_back(news);
   return "\nNoticia inserida com sucesso!";
}

//Remove uma noticia do vector
string Manager::removeNews() {
   int index = searchNews();
  
   if (index == -2) {return "\nNao existe noticia inserida!";}
   else if (index == -1) {return "\nNoticia nao encontrada!";}

   newsObjs.erase(newsObjs.begin() + index);
   return "\nNoticia removida com sucesso!";
      
}

//Mostra o nome do arquivo de todas as noticias inseridas
void Manager::showAllNews() {
   if (newsObjs.size() == 0) {
      cout << "\nNenhuma notica inserida!" << endl;
   }
   else {
      cout << "\n";
      cout << "\nNOTICIAS INSERIDAS: " << endl;
      for (unsigned index = 0; index < newsObjs.size(); index++) {
         cout << newsObjs[index].getFileName() << endl;
      }    
   }
}

//Mostra as informacoes de determinada noticia
void Manager::showNewsInformations() {
   int index = searchNews();

   if (index == -2) {
      cout << "\nNao existe noticia inserida!" << endl;
   }
   else if (index == -1) {
      cout << "\nNoticia nao encontrada!" << endl;
   }
   else {
      system("clear");
      cout << "--------------------------------INFORMACOES----------------------------------" << endl;
      cout << "\n";
      cout << "AUTOR: "                 << setw(22) << "\t" << newsObjs[index].getAuthor().getValue()   << endl; 
      cout << "CLUBE REFERIDO: "        << setw(13) << "\t" << newsObjs[index].getClub().getValue()     << endl; 
      cout << "DATA: "                  << setw(23) << "\t" << newsObjs[index].getDate().getValue()     << endl; 
      cout << "TIPO DA NOTICIA: "       << setw(12) << "\t" << newsObjs[index].getNewsKind().getValue() << endl; 
      cout << "IMPRENSA: "              << setw(19) << "\t" << newsObjs[index].getPress().getValue()    << endl; 
      cout << "TIPO DE CONFIABILIDADE: "<< setw(5) << "\t" << newsObjs[index].getTrustKind()           << endl;


   }
}

//Informa o grau de confiabilidade de uma noticia
void Manager::showTrustLevel() {
   int index = searchNews();

   if (index == -2) {
      cout << "\nNao existe noticia inserida!" << endl;
   }
   else if (index == -1) {
      cout << "\nNoticia nao encontrada!" << endl;
   }
   else {
      cout << "\nINDICE DE CONFIABILIDADE: " << endl;
      cout << "\n" << newsObjs[index].getTotalTrustLevel() << "\% de confiabilidade" << endl;
      cout << "\n";
   }

}

//Realiza se possivel a troca de times
void Manager::changeTeam() {
   string mensage, fileTeam, userTeam;
   cout << "Informe o time a ser substituido: ";
   getline(cin, fileTeam);
   cout << "\nInforme o time a ser inserido: ";
   getline(cin, userTeam);

   mensage = wrapper.getChangeTeam(fileTeam, userTeam, "changeTeam");
   cout << "\n" << mensage << endl; //Informa se a troca foi bem sucedida 
}

//Encontra as noticias sobre time informado
void Manager::findFileByClub() {
   string club;
   bool found = false;

   if (newsObjs.size() == 0) { cout << "\nNenhuma noticia inserida!" << endl; } //Vetor vazio
   else {
      cout << "Time referido: ";
      getline(cin, club); //Obtem o time referido
      cout << "\nNOTICIAS REFERIDAS A " << club << ":" << endl; 

      for(unsigned i=0; i<newsObjs.size(); i++) { //Procura no vetor de noticias
         if (club == newsObjs[i].getClub().getValue()) {
            found = true;
            cout << newsObjs[i].getFileName() << endl; //Escreve o nome do arquivo encontrado
         }
      }
      if (!found) {cout << "Nenhuma noticia inserida se refere a " << club << "!" << endl;}
   }
}

//Encontra noticas de determinado assunto (resultado, contusao, transferencia)
void Manager::findFileByNewsKind() {
   string newsKind;
   bool found = false;

   if(newsObjs.size() == 0) {cout << "\nNenhuma noticia inserida!" << endl;} //Vetor vazio
   else {
      cout << "Assunto procurado: ";
      getline(cin, newsKind); //Obtem o assunto desejado
      
      //Ignorar diferenca entre primeira letra minuscula e maiuscula
      if(newsKind == "resultado") {newsKind = "Resultado";}
      if(newsKind == "contusao") {newsKind = "Contusao";}
      if(newsKind == "transferencia") {newsKind = "Transferencia";}

      //Verificar se assunto e valido
      if ((newsKind != "Resultado") && (newsKind != "Contusao") && (newsKind != "Transferencia")) {
         cout << "\nAssunto invalido" << endl;
      }
      else {
         cout << "\nNOTICIAS SOBRE O ASSUNTO " << newsKind << ":" << endl;
         for (unsigned i = 0; i<newsObjs.size(); i++ ) {
            if (newsKind == newsObjs[i].getNewsKind().getValue()) {
               found = true;
               cout << newsObjs[i].getFileName() << endl;
            }
         }

         if (!found) { cout << "Nenhuma noticia inserida sobre o assunto " << newsKind << endl; }
         
      }

   }
}

//Tenta achar no vector a notica informada, sem devolver o nome do arquivo
int Manager::searchNews() {
   string name;
   int target = -1; //Retornar -1 se nao achar o nome

   if (newsObjs.size() == 0) {
      target = -2; //Nao tem noticia inserida, retornar -2
   }
   else {
      cout << "\nInforme o nome do arquivo da noticia: ";
      getline(cin, name);
      for (unsigned index = 0; index < newsObjs.size(); index++) {
         if (name == newsObjs[index].getFileName()) {
            target = index; //Retorna o indice do alvo
         }
      }
   }

   return target;
}

//Tenta achar no vector a noticia informada, devolvendo o nome do arquivo
int Manager::searchNews(string &str) {
   string name;
   int target = -1; //Retornar -1 se nao achar o nome

   cout << "\nInforme o nome do arquivo da noticia: ";
   getline(cin, name);
   ifstream file(name.c_str());

   if (!file) { //Verifica se o arquivo existe
      target = -2;
   }
   else {
      for (unsigned index = 0; index < newsObjs.size(); index++) {
         if (name == newsObjs[index].getFileName()) {
            target = index; //Retorna o indice do alvo
         }
      }
   str = name;
   }
   return target;
}
