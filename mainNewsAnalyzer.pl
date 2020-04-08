#   Universidade Federal do Rio de Janeiro
#   Escola Politecnica
#   Departamento de Eletronica e de Computação
#   EEL670 - Linguagens de Programacao - 2018/1
#   Prof.: Miguel Campista
#
#   Trabalho 2 - Analisador de Noticias de Futebol
#
#   Autor: Felipe Botelho Nunes da Silva


use warnings;
use strict;
use Time::localtime; 
use newsAnalyzer; #Modulo que contem as rotinas para a analise de um arquivo com noticia

my $fileName;
my $option = 0;
my $any;

while ($option != 3) {
   #Menu
   system("clear");
   print ("************************************************\n");
   print ("*******BEM VINDO AO ANALISADOR DE NOTICIAS******\n");
   print ("************************************************\n\n");
   print ("O que deseja fazer?\n\n");
   print ("1 - Analisar uma notica.\n");
   print ("2 - Trocar times no arquivo de clube.\n");
   print ("3 - Sair.\n\n");

   print ("Escolha uma opcao: ");
   $option = <STDIN>;
   chop($option);

   if (!($option =~ /\d/)) { #Se option for diferente de um digito eh invalida
      print ("OPCAO INVALIDA!\n\n");
      print ("\nPressione ENTER para continuar\n\n");
      $any = <STDIN>;
      $option = 0;
   }
   else { 
      if ($option == 1 ) { #Analisar Noticia
         print("Insira o nome do arquivo da noticia: ");
         $fileName = <STDIN>;
         chop($fileName);

         my ($criterionResult, $trustLevel);

         #Obter os valores dos criterios e as confiabilidades
         system("clear");
         print("----------------------------------------------------------------------\n");
         ($criterionResult, $trustLevel) = getPressTrustLevel($fileName);
         print("NOME DA IMPRENSA: $criterionResult;  CONFIABILIDADE: $trustLevel\n");

         ($criterionResult, $trustLevel) = getAuthorTrustLevel($fileName);
         print("NOME DO AUTOR   : $criterionResult;  CONFIABILIDADE: $trustLevel\n");

         ($criterionResult, $trustLevel) = getDateTrustLevel($fileName);
         print("DATA            : $criterionResult;  CONFIABILIDADE: $trustLevel\n");

         ($criterionResult, $trustLevel) = getClubTrustLevel($fileName);
         print("TIME REFERIDO   : $criterionResult;  CONFIABILIDADE: $trustLevel\n");

         ($criterionResult, $trustLevel) = getNewsKindTrustLevel($fileName);
         print("TIPO DA NOTICIA : $criterionResult;  CONFIABILIDADE: $trustLevel\n");
         print("----------------------------------------------------------------------\n");

         print ("\nPressione ENTER para continuar\n\n");
         $any = <STDIN>;
        
      }

      if ($option == 2 ) { #Trocar times
         print("\nInforme o time a ser removido: ");
         my $fileTeam = <STDIN>;
         print ("\nInforme o time a ser inserido: ");
         my $userTeam = <STDIN>;

         my $mensage = changeTeam ($fileTeam, $userTeam); #realiza se possivel troca, retornando a mensagem
         print ("\n\n$mensage\n");

         print ("Pressione ENTER para continuar\n\n");
         $any = <STDIN>;
      }
   }
}


