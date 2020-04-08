# Trabalho Final de Linguagens de Programação - Analisador de notícias do futebol - UFRJ

Este é o trabalho final da disciplina Linguagens de Programação do 6º período (2018-1) do curso de Engenharia Eletrônica e de Computação. O projeto consiste em implementar um sistema de análise de textos, que verificará notícias relacionadas ao mundo do futebol e obterá alguns dados e métricas. São utilizadas a linguagem _perl_, para fazer o processamento de texto, e a linguagem _C++_, responsável pela interação com o usuário e gerenciamento dos dados necessários e obtidos pela parte em _perl_.  

Antes da compilição do programa pelo Makefile (comando `make all`), é preciso instalar a biblioteca de C para perl. Portanto se utilizar um sistema Linux baseado em Debian, instalar pelo comando `sudo apt install libperl-dev`.  

Também é necessário, se não haver permissão de usuário, configuarar a variável de ambiente `PERL5LIB` para que ela encontre os módulos perl necessários no diretório escolhido. Para isso, é necessário o seguinte comando: `export PERL5LIB=/"meucaminho"`, em que _"meucaminho"_ é o caminho do diretório em que estão os arquivos do programa.  