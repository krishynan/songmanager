#include "SongManagerAux.h"

using namespace std;

int main (int argc,char **argv, char **env) {

  PERL_SYS_INIT3(&argc,&argv,&env);     /* Macro para inicialização da chamada do perl*/

  ImprimeMenu();                        /* Função geradora da interface usuário/programa */

  PERL_SYS_TERM();											/* Macro para finalizar a utilização do perl */

 return 0;
}
