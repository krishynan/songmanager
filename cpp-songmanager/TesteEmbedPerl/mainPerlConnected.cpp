#include <EXTERN.h>
#include <perl.h>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

static PerlInterpreter *my_perl;

/* Inicialização para linkar bibliotecas dinamicas ao modulo perl */
EXTERN_C void xs_init (pTHX);

EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);

EXTERN_C void
xs_init(pTHX)
{
	char *file = __FILE__;
	dXSUB_SYS;

	/* DynaLoader is a special case */
	newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
}

/* Fim da inicialização */

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

void ObtemPesquisa () {
  string busca1,busca2;

	cout << "Digite o que você deseja pesquisar: " << endl;
  getline(cin,busca1);
  cout << "Digite o termo a ser pesquisado: " << endl;
  getline(cin,busca2);

	char *busca1c = new char[busca1.length() + 1];
	strcpy(busca1c, busca1.c_str());
	char *busca2c = new char[busca2.length() + 1];
	strcpy(busca2c, busca2.c_str());

  char *args[] = {busca1c,busca2c,NULL};
  call_argv("PesquisaGlobal", G_DISCARD, args);
}

int main (int argc,char **argv, char **env) {

  char *my_argv[] = {"", "songmanager.pm"}; /* Nome do programa .pl */
//   char *args[] = {"p","Walk", NULL};

  PERL_SYS_INIT3(&argc,&argv,&env);     /* Inicialização da chamada do codigo em perl*/
  my_perl = perl_alloc();
  perl_construct (my_perl);             /* */
  perl_parse(my_perl, xs_init, 2, my_argv, NULL);
  PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

//  perl_run(my_perl);

//  call_argv("pesquisaGlobal", G_DISCARD, args);

  ObtemPesquisa();

  perl_destruct(my_perl);
  perl_free(my_perl);
  PERL_SYS_TERM();

 return 0;
}
