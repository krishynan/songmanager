#include <EXTERN.h>
#include <perl.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "SongManagerAux.h"

using namespace std;

/* Deixei pois é um exemplo de como lidar com pilha, pode ser aproveitado */

// static void BuscaAutor (string autor) {
//
//     dSP;                      /* Inicialização da pilha */
//     ENTER;
//     SAVETMPS;                 /* Criação de variáveis temporárias */
//     PUSHMARK(SP);             /* Ponteiro para pilha */
//     XPUSHs(sv_2mortal(newSViv(autor)));  /* Coloca 'a' na pilha */
//     PUTBACK;                         /* Torna o ponteiro local de pilha em global */
//     call_pv(SongManagerPerl,G_SCALAR);        /* Chamada da função do código power.pl */
//     SPAGAIN;                         /* Atualiza o ponteiro de Pilha */
//
//     printf("O autor retornado é %s.\n", POPi); /* faz o pop do valor retornado da pilha */
//     PUTBACK;
//     FREETMPS;                        /* libera os valores da pilha */
//     LEAVE;
// }
//
int main (int argc,char **argv, char **env) {

  PERL_SYS_INIT3(&argc,&argv,&env);     /* Macro para inicialização da chamada do perl, a ser realizada em ObtemPesquisa*/

  //BuscaArtista("Michael");
  ImprimeMenu();												/* Função geradora da interface usuário/programa */

  PERL_SYS_TERM();											/* Macro para finalizar a utilização do perl */

 return 0;
}
