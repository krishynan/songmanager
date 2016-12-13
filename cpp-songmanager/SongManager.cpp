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

void ObtemPesquisa (string buscado, string termo, string termo2)
{

	char *buscac = new char[buscado.length() + 1];
	strcpy(buscac, buscado.c_str());
	char *termoc = new char[termo.length() + 1];
	strcpy(termoc, termo.c_str());
	char *termo2c = new char[termo2.length() + 1];
	strcpy(termo2c, termo2.c_str());
	cout << endl;
  if (strcmp(termo2c,"NULL")) {
    char *args[] = {buscac,termoc,termo2c,NULL};
    call_argv("PesquisaGlobal", G_DISCARD, args);
  }
  else {
    char *args[] = {buscac,termoc,NULL};
    call_argv("PesquisaGlobal", G_DISCARD, args);
  }
}

void ImprimeMenu () {

      int i = 1;
      string busca,busca2;

      cout << "Olá, bem-vindo ao menu de seleção do SongManager!" << endl
         << "Escolha 1 para Pesquisa por um autor. Retorna todas musicas do autor se for exato" << endl
         << "Escolha 2 para Pesquisa por um titulo. Retorna a musica inteira se for exato" << endl
         << "Escolha 3 para Pesquisa por um ano de lancamento. Retorna os nomes das musicas" << endl
         << "Escolha 4 para Pesquisa por um trecho. Retorna o titulo e um pedaco do trecho achado" << endl
         << "Escolha 5 para Pesquisa por DOIS trechos desconectados. Retorna o titulo e um pedaco do trecho achado" << endl
         << "Escolha 0 para sair do programa." << endl;
         while (i != 0) {
           cout << "\nEscolha a opção desejada:" << endl;
           cin >> i;
           cin.ignore();
           switch (i) {
             case 1:
                 cout << "Digite o autor a ser buscado:" << endl;
                 getline(cin,busca);
                 ObtemPesquisa("Autor",busca,"NULL");
                 break;
             case 2:
                 cout << "Digite o titulo a ser buscado:" << endl;
                 getline(cin,busca);
                 ObtemPesquisa("Titulo",busca,"NULL");
                 break;

             case 3:
                 cout << "Digite o ano a ser buscado:" << endl;
                 getline(cin,busca);
                 ObtemPesquisa("Lan",busca,"NULL");
                 break;

             case 4:
                 cout << "Digite o trecho a ser buscado:" << endl;
                 getline(cin,busca);
                 ObtemPesquisa("Peda",busca,"NULL");
                 break;

             case 5:
                 cout << "Digite o primeiro trecho a ser buscado:" << endl;
                 getline(cin,busca);
                 cout << "Digite o segundo trecho a ser buscado:" << endl;
                 getline(cin,busca2);
                 ObtemPesquisa("Dupla",busca,busca2);
                 break;
             case 0:
                 break;
           }
         }
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
	ObtemPesquisa("A","Michael", "BEE");
  ImprimeMenu();

  perl_destruct(my_perl);
  perl_free(my_perl);
  PERL_SYS_TERM();

 return 0;
}
