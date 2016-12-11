#include <iostream>
#include <string>
#include "menu.h"

using namespace std;

int main () {
  int i = 1;
  string busca;
  string busca2; //A ser utilizado quando o usuário deseja buscar dois trechos

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
          menuOpcao1(busca);
          break;
      case 2:
          cout << "Digite o titulo a ser buscado:" << endl;
          getline(cin,busca);
          menuOpcao2(busca);
          break;

      case 3:
          cout << "Digite o ano a ser buscado:" << endl;
          getline(cin,busca);
          menuOpcao3(busca);
          break;

      case 4:
          cout << "Digite o trecho a ser buscado:" << endl;
          getline(cin,busca);
          menuOpcao4(busca);
          break;

      case 5:
          cout << "Digite o primeiro trecho a ser buscado:" << endl;
          getline(cin,busca);
          cout << "Digite o segundo trecho a ser buscado:" << endl;
          getline(cin,busca2);
          menuOpcao5(busca,busca2);
          break;
      case 0:
          break;
    }
  }
 return 0;
}
