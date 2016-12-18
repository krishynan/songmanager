#include <EXTERN.h>
#include <perl.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "SongManagerAux.h"

using namespace std;

int main (int argc,char **argv, char **env) {

  PERL_SYS_INIT3(&argc,&argv,&env);     /* Macro para inicialização da chamada do perl, a ser realizada em ObtemPesquisa*/

  newMusicFile("Hello_Adele");
  //BuscaArtista("Michael");
  ImprimeMenuPesquisa();												/* Função geradora da interface usuário/programa */

  PERL_SYS_TERM();											/* Macro para finalizar a utilização do perl */

 return 0;
}
