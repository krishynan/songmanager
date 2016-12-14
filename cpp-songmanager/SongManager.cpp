#include <EXTERN.h>
#include <perl.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "SongManagerAux.h"

using namespace std;

/* Deixei pois é um exemplo de como lidar com pilha, pode ser aproveitado */

// static void BuscaAutor (int a, int b) {
//
//     dSP;                      /* Inicialização da pilha */
//     ENTER;
//     SAVETMPS;                 /* Criação de variáveis temporárias */
//     PUSHMARK(SP);             /* Ponteiro para pilha */
//     XPUSHs(sv_2mortal(newSViv(a)));  /* Coloca 'a' na pilha */
//     XPUSHs(sv_2mortal(newSViv(b)));  /* Coloca 'b' na pilha */
//     PUTBACK;                         /* Torna o ponteiro local de pilha em global */
//     call_pv("expo",G_SCALAR);        /* Chamada da função do código power.pl */
//     SPAGAIN;                         /* Atualiza o ponteiro de Pilha */
//
//     printf("%d to the %d power is %d.\n", a,b, POPi); /* faz o pop do valor retornado da pilha */
//     PUTBACK;
//     FREETMPS;                        /* libera os valores da pilha */
//     LEAVE;
// }
//
int main (int argc,char **argv, char **env) {


  PERL_SYS_INIT3(&argc,&argv,&env);     /* Macro para inicialização da chamada do perl, a ser realizada em ObtemPesquisa*/

  ImprimeMenu();												/* Função geradora da interface usuário/programa */

  PERL_SYS_TERM();											/* Macro para finalizar a utilização do perl */

 return 0;
}
