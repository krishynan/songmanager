#include <EXTERN.h>
#include <perl.h>
#include <cstdlib>
#include <iostream>

using namespace std;

static PerlInterpreter *my_perl;

static void PerlPower (int a, int b) {

    dSP;                      /* Inicialização da pilha */
    ENTER;
    SAVETMPS;                 /* Criação de variáveis temporárias */
    PUSHMARK(SP);             /* Ponteiro para pilha */
    XPUSHs(sv_2mortal(newSViv(a)));  /* Coloca 'a' na pilha */
    XPUSHs(sv_2mortal(newSViv(b)));  /* Coloca 'b' na pilha */
    PUTBACK;                         /* Torna o ponteiro local de pilha em global */
    call_pv("expo",G_SCALAR);        /* Chamada da função do código power.pl */
    SPAGAIN;                         /* Atualiza o ponteiro de Pilha */

    printf("%d to the %d power is %d.\n", a,b, POPi); /* faz o pop do valor retornado da pilha */
    PUTBACK;
    FREETMPS;                        /* libera os valores da pilha */
    LEAVE;
}


int main (int argc,char **argv, char **env) {

  char *my_argv[] = {"", "power.pl"}; /* Nome do programa .pl */

  if (argc != 3) {
    cout << "Uso: ./power [int] [int]\n" << endl;
    return 1;
  }

  int i, j;
  i = atoi(argv[1]);
  j = atoi(argv[2]);


  PERL_SYS_INIT3(&argc,&argv,&env);     /* Inicialização da chamada do codigo em perl*/
  my_perl = perl_alloc();
  perl_construct (my_perl);             /* */
  perl_parse(my_perl, NULL, 2, my_argv, (char **)NULL);
  PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
  perl_run(my_perl);

  PerlPower(i,j);

  perl_destruct(my_perl);
  perl_free(my_perl);
  PERL_SYS_TERM();

 return 0;
}
