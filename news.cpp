/* EEL670 - Linguagens de Programacao - 2018/1
   Prof.: Miguel Campista

   Trabalho 3 - Analisador de Noticias de Futebol

   Autor: Felipe Botelho Nunes da Silva
*
*/

#include "news.h"

News::News(string name) : fileName(name), trustKind("Nao Identificado"), totalTrustLevel(0),
                          author(), club(), date(), newsKind(), press() {}


string News::getFileName() {
   return fileName;
}

//Analisa a noticia, determinando os atributos
void News::analyzeNews(PerlWrapper &perlwrapper) {
   string value;
   unsigned trustLevel;

   //Fazer interfaceamento com o perl
   //PerlWrapper perlwrapper("");
   //perlwrapper.runInterpreter();

   //Pegar valores para criterio author
   trustLevel = perlwrapper.getTrustLevel(fileName, value, "getAuthorTrustLevel");
   author.setValue(value);
   author.setTrustLevel(trustLevel);
  
   //Pegar valores para criterio club
   trustLevel = perlwrapper.getTrustLevel(fileName, value, "getClubTrustLevel");
   club.setValue(value);
   club.setTrustLevel(trustLevel);
   
   //Pegar valores para criterio date
   trustLevel = perlwrapper.getTrustLevel(fileName, value, "getDateTrustLevel");
   date.setValue(value);
   date.setTrustLevel(trustLevel);
   
   //Pegar valores para criterio newsKind
   trustLevel = perlwrapper.getTrustLevel(fileName, value, "getNewsKindTrustLevel");
   newsKind.setValue(value);
   newsKind.setTrustLevel(trustLevel);

   //Pegar valores para criterio press
   trustLevel = perlwrapper.getTrustLevel(fileName, value, "getPressTrustLevel");
   press.setValue(value);
   press.setTrustLevel(trustLevel);

   setTotalTrustLevel();
}

//Retorna o tipo de confiabilidade (confiavel, insegura ou falsa)
string News::getTrustKind() {
   return trustKind;
}

//Retorna a confiabilidade da noticia
unsigned News::getTotalTrustLevel() {
   return totalTrustLevel;
}

//Retorna o criterio author
Criterion &News::getAuthor() {
   return author;
}

//Retorna o criterio club
Criterion &News::getClub() {
   return club;
}

//Retorna o criterio date
Criterion &News::getDate() {
   return date;
}

//Retorna o criterio newsKind
Criterion &News::getNewsKind() {
   return newsKind;
}

//Retorna o criterio press
Criterion &News::getPress() {
   return press;
}

//Analisa as confiabilidade de cada criterio para determinar a confiabilidade da noticia
void News::setTotalTrustLevel() {
   totalTrustLevel = (4*press.getTrustLevel() + 3*author.getTrustLevel() 
                     + 3*date.getTrustLevel() + club.getTrustLevel() + newsKind.getTrustLevel()) / 12;

   setTrustKind();
}

//Determina o tipo de confiabilidade da noticia (verdadeira, insegura ou falsa)
void News::setTrustKind() {
   if(totalTrustLevel <= 49 ) {
      trustKind = "Falsa";
   }
   else if((totalTrustLevel > 49) && (totalTrustLevel <= 69)) {
      trustKind = "Insegura";
   }
   else {
      trustKind = "Verdadeira";
   }
}
