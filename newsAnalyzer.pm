#   Universidade Federal do Rio de Janeiro
#   Escola Politecnica
#   Departamento de Eletronica e de Computação
#   EEL670 - Linguagens de Programacao - 2018/1
#   Prof.: Miguel Campista
#
#   Trabalho 2 - Analisador de Noticias de Futebol
#
#   Autor: Felipe Botelho Nunes da Silva


package newsAnalyzer;

use 5.016003;
use strict;
use warnings;
use Time::localtime;

require Exporter;

our @ISA = qw(Exporter);

# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.

# This allows declaration	use newsAnalyzer ':all';
# If you do not need this, moving things directly into @EXPORT or @EXPORT_OK
# will save memory.
our %EXPORT_TAGS = ( 'all' => [ qw(
	
) ] );

our @EXPORT_OK = qw ( @{ $EXPORT_TAGS{'all'} } );

our @EXPORT = qw( 
                  changeTeam
                  getAuthorTrustLevel
                  getClubTrustLevel
                  getDateTrustLevel
                  getNewsKindTrustLevel
                  getPressTrustLevel
);

our $VERSION = '0.01';


#******************************************SUBROTINAS**********************************************************

#Funcao que troca um clube do arquivo times.txt por um outro que nao esteja no arquivo informado pelo usuario
sub changeTeam {
   my ($fileTeam, $userTeam) = @_;

   open (my $in, "<", "times.txt") or die "Nao foi possivel abrir arquivo: $!";
   local $/ = undef;  #Perde a referencia de nova linha, para depois poder atribuir todo arquivo em uma variavel escalar
   my $allData = <$in>; #Atribui todo o arquivo a variavel escalar
   close $in or die "Nao foi possivel fechar arquivo: $!";

   if ($allData =~ /$userTeam/) {
      return "O clube a ser inserido ja existe no arquivo de times!\n";
   }
   else {
      if ($allData =~ /$fileTeam/) {
         $allData =~ s/$fileTeam/$userTeam/; #Modifica o time requerido
         #Escreve no arquivo com a modificacao
         open (my $out, ">", "times.txt") or die "Nao foi possivel abrir arquivo: $!";
         print $out $allData; #Escreve no arquivo
         close $out or die "Nao foi possivel fechar arquivo: $!";
         return "Troca efetuada!";
      }
      else {
         return "O time a ser substituido nao existe no arquivo de times!\n";
      }
   }
}


#Funcao que identifica e retorna o nome do autor da noticia em um arquivo de texto, e 
#retorna a confiabilidade
sub getAuthorTrustLevel {
   my $newsFileName = $_[0];
   my $lineCount = 1;
   my $line;
   my $author = "Nao encontrado";

   open (my $in, "<", $newsFileName) or die "Nao foi possivel abrir arquivo: $!";
   while (<$in>) {
      if ($lineCount == 2) { #Linha no arquivo onde deve esta presente o nome
         $line = $_;
         if ($line =~ /Por\s(\D+)\n/i) { #Nome identificado apos a palavra 'Por'
            $author = $1;
         }
      } 
      $lineCount++;
   }

   if ($author eq "Nao encontrado") {
      return ($author, 40); #Nao ha nome do autor, confiabilidade 40
   }
   else {
      return ($author, 100); #Encontrou o nome, confiabilidade 100
   }
}


#Fucao que avalia sobre qual time se trata o arquivo com a notica informada, retornando
#esse time e um indice de confiabilidade
sub getClubTrustLevel {
   my $newsFileName = $_[0];
   my %freqClubs; #Hash que tera os times(chave) e o numero de vezes(valor) que apareceram na notica

   #Analisar o arquivo de times
   open (my $in1, "<", "times.txt") or die "Nao foi possivel abrir arquivo: $!";
   while (<$in1>) {
      my $club = $_; #Time a ser analisado
      my @equals;
      my $frequency = 0;

      chop($club);
      #Obter quantas vezes o time aparece no arquivo da noticia
      open (my $in2, "<", $newsFileName) or die "Nao foi possivel abrir arquivo: $!";
      while (<$in2>) {
         if (@equals = $_ =~ /$club/gi) {
            $frequency = $frequency + scalar @equals;
         }
      }
      close $in2 or die "Nao foi possivel fechar arquivo: $!";
      $freqClubs{$club} = $frequency; #Atribui na hash o time(chave) e o numero de aparicoes(valor)
   }
   close $in1 or die "Nao foi possivel fechar arquivo: $!";
   
   #Analisar pela hash qual time apareceu mais vezes
   my $relevantClub = "Nao Identificado";
   my $relevantFrequency = 0;
   my $trustLevel = 30;

   foreach my $k (keys %freqClubs) {
      if ($freqClubs{$k} > $relevantFrequency) {
         $relevantClub = $k;
         $relevantFrequency = $freqClubs{$k};
      }
   }
   if ($relevantFrequency == 1) {
      $trustLevel = 80; #Time mais relevante com somente 1 aparicao tem confiabilidade 80
   }
   elsif ($relevantFrequency > 1) { 
      $trustLevel = 100; #Time mais relevante com mais de 1 aparicao tem confiabilidade 100
   }
   #Retorna o time mais relevante e o indice de confiabilidade
   return ($relevantClub, $trustLevel);
}


#Funcao que compara a data(ano) da noticia com a atual e atribui uma confiabilidade quanto a isso
sub getDateTrustLevel {
   my $newsFileName = $_[0];
   my %newsDate;
   my $line;
   my $found = 0; #Indica se ha data no arquivo

   #Pegar a data do arquivo de notica
   open (my $in, "<", $newsFileName) or die "Nao foi possivel abrir arquivo: $!";
   while (<$in>) {
      $line = $_;
      #Comparar se line eh da forma d/d/d, em que d eh formado apenas por digitos
      if ($line =~ /(\d+)\/(\d+)\/(\d+)/) {
         $found = 1;
         %newsDate = (
            day => $1, #Atribui o dia
            month => $2, #Atribui o mes
            year => $3,  #Atribui o ano
         );
      }
   }
   close $in or die "Nao foi possivel fechar arquivo: $!";
   
   if ($found == 0) { #Nao encontrou data
      return ("Nao Identificado", 50); #Retorna confiabilidade 50
   }

   #Se encontrou data, pegar o ano da data atual
   my $tm = localtime;
   my $todayYear = $tm->year + 1900;
   #Comparar os anos e retornar o nivel de confiabilidade e a data completa da noticia
   my $newsDateString = "$newsDate{day}/$newsDate{month}/$newsDate{year}";
 
   if ($newsDate{year} > $todayYear) {
      return ($newsDateString, 50);
   } 
   else {
      return ($newsDateString, 100);
   }
}


#Funcao que localiza palavras chaves na notica para classifica-la como do tipo Resultado, Contusao ou Transferencia e atribui
#um nivel de confiabilidade quanto a isso
sub getNewsKindTrustLevel {
   #Palavras chave
    my @RESULTADO_KEY_WORDS = ("\\dx\\d", "vitoria", "partida", "resultado", "perd(?:eu|edor|ia)", "derrot(?:a|ado|ou|ava)", "venc(?:eu|ido|ia|edor)", "empat(?:e|ou|ar)");
   #O valor '\\dx\\dx' eh para indicar a busca por resultados de partida, do tipo dxd, em que d eh um digito

   my @CONTUSAO_KEY_WORDS = ("contusao","les(?:ao|ionado|ionou)","machuc(?:ou|ado)");
   my @TRANSFERENCIA_KEY_WORDS = ("transferencia", "val(?:or|ores|orizado)", "R\$", "reais", "dolares", "vend(?:a|ido|eu)", "emprest(?:imo|ou|ado)", "negoci(?:o|ar|acao)", "especul(?:ar|acao)");


   my @KEY_WORDS_REF = (\@RESULTADO_KEY_WORDS, \@CONTUSAO_KEY_WORDS, \@TRANSFERENCIA_KEY_WORDS);
   my $newsFileName = $_[0];
   my $line;
   my @equals;
   my $keyWord;
   my $arrayRef;
   my ($resultadoCount, $contusaoCount, $transfCount) = (0,0,0);

   open (my $in, "<", $newsFileName) or die "Nao foi possivel abrir arquivo: $!";
   while (<$in>) {
      $line = $_;
      #Identificar na linha do arquivo as ocorrencias de palavras nos arrays de palavras-chave
      for (my $count = 0; $count < 3; $count++) {
         $arrayRef = $KEY_WORDS_REF[$count];
         foreach (@{$arrayRef}) { #Avaliar cada palavra do array de palavras-chave
            $keyWord = $_;
            if (@equals = $line =~ /$keyWord/gi) {
               if ($count == 0) { $resultadoCount += scalar @equals;}
               if ($count == 1) { $contusaoCount += scalar @equals;}
               if ($count == 2) { $transfCount += scalar @equals;}
            }
         }
      }
   }
   close $in or die "Nao foi possivel fechar arquivo: $!";
   
   #Identificar tipo da noticia e confiablidade
   my $newsKind;
   my $trustLevel;
   my $total = $resultadoCount + $contusaoCount + $transfCount;

   if (($resultadoCount > $contusaoCount) and ($resultadoCount > $transfCount)) { #resultadoCount maior
      $newsKind = "Resultado";
      $trustLevel = ((1 + $resultadoCount/$total)/2)*100; #Calcular confiabilidade
   }
   elsif (($contusaoCount > $resultadoCount) and ($contusaoCount > $transfCount)) { #contusaoCount maior
      $newsKind = "Contusao";
      $trustLevel = ((1 + $contusaoCount/$total)/2)*100; #Calcular confiabilidade
   }
   elsif (($transfCount > $resultadoCount) and ($transfCount > $contusaoCount)) { #transfCount maior
      $newsKind = "Transferencia";
      $trustLevel = ((0.8 + $transfCount/$total)/2)*100;
   }
   else {
      $newsKind = "Nao identificado";
      $trustLevel = 40;
   }
   $trustLevel = sprintf("%.0f", $trustLevel); #Aproximar numero para nao exibir decimal
   return ($newsKind, $trustLevel);
}


#Funcao que identifica a imprensa da noticia informada e sua confiabilidade
sub getPressTrustLevel {
   my $newsFileName = $_[0];
   my $achou = 0;
   my $line;
   my $press;
   my $trustLevel;

   #Encontrar no arquivo da noticia o nome da imprensa esportiva
   open (my $in, "<", $newsFileName) or die "Nao foi possivel abrir arquivo: $!";
   $press = <$in>; #Nome se encontra na primeira linha do arquivo
   close $in or die "Nao foi possivel fechar arquivo: $!";
   
   chop $press;

   #Verificar se no arquivo de imprensas existe o nome encontrado no arquivo de noticia e obter
   #o nivel de confiabilidade
   open (my $in2, "<", "jornais.txt") or die "Nao foi possivel abrir arquivo: $!";
   while (<$in2>) {
      $line = $_;
      if ($line =~ /($press)=(\d+)/) { #Obter a confiabilidade
         $achou = 1;   
         $trustLevel = $2;
      }
   }
   close $in2 or die "Nao foi possivel fechar arquivo: $!";

   #Se nao achar no arquivo de imprensa, atribuir confiabilidade 50
   if ($achou == 0) {
      $trustLevel = 50;
   }
   return ($press, $trustLevel);
}


1;
__END__
