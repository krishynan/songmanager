#include "SongManagerAux.h"
#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>

using namespace std;


char * ConverteStringChar (string entrada)
{
	char *saida = new char[entrada.length() + 1];
	strcpy(saida, entrada.c_str());
	return saida;
}

// EXTERN_C void xs_init (pTHX);
//
// EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);

/* Inicialização para linkar bibliotecas dinamicas ao modulo perl */
EXTERN_C void xs_init(pTHX)
{
	char *file = ConverteStringChar(__FILE__);
	dXSUB_SYS;

	/* DynaLoader is a special case */
	newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
}

/* Fim da inicialização */

void ObtemPesquisa (char *busca, char *termo, char *termo2)
{
	char *my_argv[] = {ConverteStringChar(""), ConverteStringChar("songmanager.pm")}; /* Nome do programa .pl */
	my_perl = perl_alloc();
  perl_construct (my_perl);             /* */
  perl_parse(my_perl, xs_init, 2, my_argv, NULL);
  PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

  if (termo2 != NULL) {
    char *args[] = {busca,termo,termo2,NULL};
    call_argv("PesquisaGlobal", G_DISCARD, args);
  }
  else {
    char *args[] = {busca,termo,NULL};
    call_argv("PesquisaGlobal", G_DISCARD, args);
  }

	perl_destruct(my_perl);
	perl_free(my_perl);

}

void ImprimeMenu () {

      int i=1;
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
                 ObtemPesquisa(ConverteStringChar("Autor"),ConverteStringChar(busca),NULL);
                 break;
             case 2:
                 cout << "Digite o titulo a ser buscado:" << endl;
                 getline(cin,busca);
                 ObtemPesquisa(ConverteStringChar("Titulo"),ConverteStringChar(busca),NULL);
                 break;

             case 3:
                 cout << "Digite o ano a ser buscado:" << endl;
                 getline(cin,busca);
                 ObtemPesquisa(ConverteStringChar("Lançamento"),ConverteStringChar(busca),NULL);
                 break;

             case 4:
                 cout << "Digite o trecho a ser buscado:" << endl;
                 getline(cin,busca);
                 ObtemPesquisa(ConverteStringChar("Pedaço"),ConverteStringChar(busca),NULL);
                 break;

             case 5:
                 cout << "Digite o primeiro trecho a ser buscado:" << endl;
                 getline(cin,busca);
                 cout << "Digite o segundo trecho a ser buscado:" << endl;
                 getline(cin,busca2);
                 ObtemPesquisa(ConverteStringChar("Dupla"),ConverteStringChar(busca),ConverteStringChar(busca2));
                 break;
             case 0:
                 break;
           }
         }
}
