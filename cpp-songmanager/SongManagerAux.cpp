#include "SongManagerAux.h"
#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>

using namespace std;


void ObtemPesquisa (string busca, string termo, string termo2)
{
	char *buscac = new char[busca.length() + 1];
	strcpy(buscac, busca.c_str());
	char *termoc = new char[termo.length() + 1];
	strcpy(termoc, termo.c_str());

  if (!(termo2.empty())) {
    char *termo2c = new char[termo2.length() + 1];
    strcpy(termo2c, termo2.c_str());
    char *args[] = {buscac,termoc,termo2c,NULL};
    call_argv("PesquisaGlobal", G_DISCARD, args);
  }
  else {
    char *args[] = {buscac,termoc,NULL};
    call_argv("PesquisaGlobal", G_DISCARD, args);
  }
}

void ImprimeMenu () {

      int i;
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
                 ObtemPesquisa("Autor",busca,NULL);
                 break;
             case 2:
                 cout << "Digite o titulo a ser buscado:" << endl;
                 getline(cin,busca);
                 ObtemPesquisa("Titulo",busca,NULL);
                 break;

             case 3:
                 cout << "Digite o ano a ser buscado:" << endl;
                 getline(cin,busca);
                 ObtemPesquisa("Lançamento",busca,NULL);
                 break;

             case 4:
                 cout << "Digite o trecho a ser buscado:" << endl;
                 getline(cin,busca);
                 ObtemPesquisa("Pedaço",busca,NULL);
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
