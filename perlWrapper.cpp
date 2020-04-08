/* EEL670 - Linguagens de Programacao - 2018/1
   Prof.: Miguel Campista

   Trabalho 3 - Analisador de Noticias de Futebol

   Autor: Felipe Botelho Nunes da Silva
*/

#include <stddef.h>
#include "perlWrapper.h"

PerlWrapper::PerlWrapper(string script = "teste") {
   //PERL_SYS_INIT3(NULL, NULL, NULL);
   int dummy_argc = 0;
   char*** dummy_env = 0;
   //char string[] = {};
   //char* dummy_argv[] = {string, &script[0]};

   PERL_SYS_INIT3(&dummy_argc, dummy_env, dummy_env);
   
   my_perl = perl_alloc();
   perl_construct(my_perl);
   PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
}

PerlWrapper::~PerlWrapper() {
   perl_destruct(my_perl);
   perl_free(my_perl);
   PERL_SYS_TERM();
}

//void PerlWrapper::runInterpreter(char *file) {
void PerlWrapper::runInterpreter() {
   //my_argv[0] = "";
   //my_argv[1] = file;
   char _MYARGV_PERL_MODULE_NAME[] = "perlUses.pl";
   char _MYARGV_NOTHING_NAME[] = "";
   char *my_argv[] = {static_cast<char*>(_MYARGV_NOTHING_NAME), static_cast<char*>(_MYARGV_PERL_MODULE_NAME)};
   perl_parse(my_perl, 0, 2, my_argv, (char **)NULL);
   perl_run(my_perl);
}

int PerlWrapper::getTrustLevel(string fileNews, string &value, string perlFunc) {
   dSP;
   ENTER;
   SAVETMPS;
   PUSHMARK(SP);
   XPUSHs(sv_2mortal(newSVpv(fileNews.c_str(), fileNews.length()))); 
   XPUSHs(sv_2mortal(newSVpv(value.c_str(), value.length())));
   PUTBACK;
   call_pv(perlFunc.c_str(), G_ARRAY);
   SPAGAIN;

   int result = POPi;
   value = POPp;
   PUTBACK;
   FREETMPS;
   LEAVE;

   return result;
}

string PerlWrapper::getChangeTeam(string fileTeam, string userTeam, string perlFunc) {
   dSP;
   ENTER;
   SAVETMPS;
   PUSHMARK(SP);
   XPUSHs(sv_2mortal(newSVpv(fileTeam.c_str(), fileTeam.length())));
   XPUSHs(sv_2mortal(newSVpv(userTeam.c_str(), userTeam.length())));
   PUTBACK;
   call_pv(perlFunc.c_str(), G_SCALAR);
   SPAGAIN;

   string result = POPp;
   PUTBACK;
   FREETMPS;
   LEAVE;

   return result;
}
