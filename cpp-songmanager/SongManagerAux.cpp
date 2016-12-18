#include "SongManagerAux.h"
#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>

using namespace std;

void ImprimeMusica (Musica musica) {
		musica.getMusicaInteira();
}

char * ConverteStringChar (string entrada)
{
	char *saida = new char[entrada.length() + 1];
	strcpy(saida, entrada.c_str());
	return saida;
}

string InsereDiretorio (string nome_arquivo)
{
	string result;
	result = (DIRETORIO_DE_MUSICAS + nome_arquivo);
	return result;
}

void NovaMusica(string newFile) {
	int contador=1;

	string result;
	ostringstream conversora;
	conversora << DIRETORIO_DE_MUSICAS << "song" << contador << ".txt"; //<< contador << ".txt";
	result = conversora.str();


	while (file_exists(ConverteStringChar(result))){
		conversora.str("");
		conversora.clear();
		conversora << DIRETORIO_DE_MUSICAS << "song" << contador << ".txt"; //<< contador << ".txt";
		result = conversora.str();
		contador++;
	}

	ifstream  arquivo_origem(ConverteStringChar(newFile));
	if (arquivo_origem.is_open()) {
  ofstream  arquivo_destino(ConverteStringChar(result));
	arquivo_destino << arquivo_origem.rdbuf();
	cout << "Musica " << newFile << " adicionada com sucesso" << endl;
  }
	else cout << "Erro ao adicionar música" << endl;

	arquivo_origem.close();
}

bool file_exists(const char *fileName)
{
    ifstream infile(fileName);
    return infile.good();
}

void RemoveMusica (string titulo)
{
	int escolha = 1;
	vector <Musica> lista = BuscaMusica(titulo,escolha);
	string decisao;
	int i,indice;

	for (i = 0; i < lista.size();i++){
	cout << "Para excluir a musica " << lista[i].getTitulo() << "\t" << lista[i].getNomeArquivo() << " digite " << (i+1) <<  endl;
  }
	cout << "Digite 0 para cancelar e voltar ao menu." << endl;
	cin >> indice;
	cin.ignore();
	if (indice > lista.size())
	{
		cout << "A musica selecionada não existe!" << endl;
	}
	else if (indice == 0) {}
	else {
	if( remove(lista[indice-1].getNomeArquivo()) != 0 )
    perror( "Erro ao apagar arquivo" );
  else
    cout << "Musica apagada com sucesso" << endl;
	}
}


/* Inicialização para linkar bibliotecas dinamicas ao modulo perl */
EXTERN_C void xs_init(pTHX)
{
	char *file = ConverteStringChar(__FILE__);
	dXSUB_SYS;

	/* DynaLoader is a special case */
	newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
}
/* Fim da inicialização */


/* Função que imprime os resultados da busca(exceto busca por artista e titulo) realizada pelo usuário. */
void ObtemPesquisa (char *busca, char *termo, char *termo2)
{
	char *my_argv[] = {ConverteStringChar(""), ConverteStringChar(SongManagerPerl)}; /* Nome do programa .pl */
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

/* Retorna todas as musicas para o artista procurado */
void RetornaMusicasArtista (vector <string> resultados) {
	string decisao;
	int i,indice;

	for (i = 0; i < resultados.size();i++){
	cout << "Para visualizar todas as musicas do artista " << resultados[i] << " digite " << (i+1) << endl;
  }
	cout << "Digite 0 para voltar ao menu de pesquisa." << endl;
	cin >> indice;
	cin.ignore();
	if (indice > resultados.size())
	{
		cout << "O artista selecionado não existe!" << endl;
	}
	else if (indice == 0) {}
	else {ObtemPesquisa(ConverteStringChar("Autor"),ConverteStringChar(resultados[indice -1]),NULL);}
}

/* Realiza a busca por artista e gera um vetor de resultados com os possiveis artistas compatíveis com a pesquisa.
	 Também chama a função RetornaMusicasArtista para o usuário visualizar quais músicas do artista pesquisado existem no diretório
*/
void BuscaArtista (string autor) {
	vector <string> resultado;
	string retornoPilha;
	int i = -1;

	char *my_argv[] = {ConverteStringChar(""), ConverteStringChar(SongManagerPerl)}; /* Nome do programa .pl */
	my_perl = perl_alloc();
	perl_construct (my_perl);             /* */
	perl_parse(my_perl, xs_init, 2, my_argv, NULL);
	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

  dSP;                      /* Inicialização da pilha */
  ENTER;
  //SAVETMPS;                 /* Criação de variáveis temporárias */
  PUSHMARK(SP);             /* Ponteiro para pilha */
  //XPUSHs(sv_2mortal((newSVpv(ConverteStringChar(autor),autor.length()))));  /* Coloca autor na pilha */
  //PUTBACK;                         /* Torna o ponteiro local de pilha em global */
	char *args[] = {ConverteStringChar("Autor"),ConverteStringChar(autor),NULL};

  call_argv("PesquisaGlobal", G_ARRAY, args);
  SPAGAIN;                         /* Atualiza o ponteiro de Pilha */
	//cout << "O autor retornado é \n" <<  POPp  << '\t' << POPp << endl; /* faz o pop do valor retornado da pilha */

	do {
		 i++;
		 //cout << i << '\t';
		 retornoPilha = POPp;
		 if (!(retornoPilha.empty())) {resultado.push_back(retornoPilha);}
		 //cout << resultado[i] << endl;
	 } while(!(retornoPilha.empty()));

  PUTBACK;
  FREETMPS;                        /* libera os valores da pilha */
  LEAVE;

	perl_destruct(my_perl);
	perl_free(my_perl);

	RetornaMusicasArtista(resultado);
}


/* Função que exibe o resultado da busca por musicas e imprime na tela a musica inteira*/
void RetornaMusicaInteira (vector <Musica> resultados) {
	string decisao;
	int i,indice;

	for (i = 0; i < resultados.size();i++){
	cout << "Para exibir a letra inteira da musica " << resultados[i].getTitulo() << '\t' << resultados[i].getNomeArquivo() << " digite " << (i+1) <<  endl;
  }
	cout << "Digite 0 para voltar ao menu de pesquisa." << endl;
	cin >> indice;
	cin.ignore();
	if (indice > resultados.size())
	{
		cout << "A musica selecionada não existe!" << endl;
	}
	else if (indice == 0) {}
	else {resultados[indice-1].getMusicaInteira();}
}


/* Realiza a busca por musicas e gera um vetor de resultados com as possiveis musicas compatíveis com a pesquisa.
	 Também chama a função RetornaMusicaInteira para o usuário visualizar a letra inteira de uma musica
*/
vector <Musica> BuscaMusica (string musica, int escolha) {
	int i = -1;
	vector <Musica> resultados;
	Musica musicaResultante;
	//vector <string> resultado;
	string retornoPilha;

	char *my_argv[] = {ConverteStringChar(""), ConverteStringChar(SongManagerPerl)}; /* Nome do programa .pl */
	my_perl = perl_alloc();
	perl_construct (my_perl);             /* */
	perl_parse(my_perl, xs_init, 2, my_argv, NULL);
	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

  dSP;
  ENTER;
  PUSHMARK(SP);             																										 /* Ponteiro para pilha */

	char *args[] = {ConverteStringChar("Titulo"),ConverteStringChar(musica),NULL}; /*Argumentos a serem passados para a subrotina do .pm */

  call_argv("PesquisaGlobal", G_ARRAY, args); 																   /* Chamada da subrotina */
  SPAGAIN;                         																							 /* Atualiza o ponteiro de Pilha */

	do {																																					 /* Rotina de repetição para salvar todos os resultados */
		 retornoPilha = POPp;																												 /* obtidos a partir da busca por titulo em um vetor de Musicas*/
		 if (!(retornoPilha.empty())) {
			 musicaResultante.setNomeArquivo(ConverteStringChar(retornoPilha));
		 	 retornoPilha = POPp;
			 if (!(retornoPilha.empty())) {
			   	musicaResultante.setTitulo(retornoPilha);
				}
		}
		 if (!(retornoPilha.empty()))
		 {
			 resultados.push_back(musicaResultante);
		 }
	 } while(!(retornoPilha.empty()));

  PUTBACK;
  FREETMPS;                       																								/* libera os valores da pilha */
  LEAVE;

	perl_destruct(my_perl);
	perl_free(my_perl);

	if (escolha == 0) {RetornaMusicaInteira(resultados);}                       												/* Chama a função responsável por listar os resultados e */																																										/* imprimir a musica inteira. 													 */\

	return resultados;
}

/* Imprime o submenu para o usuário realizar uma pesquisa por Artista, Título, Data, Trecho ou Dupla
	 Também chama a função de busca correspondente com a seleção do usuário, passando o termo pesquisado para a função.
	*/
void ImprimeMenuPesquisa () {
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
						 BuscaArtista(busca);
             break;
         case 2:
             cout << "Digite o titulo a ser buscado:" << endl;
             getline(cin,busca);
						 BuscaMusica(busca,0);
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


void ImprimeMenu () {
  int i=1;
  string entrada;
     while (i != 0) {
  	 cout << "Olá, bem-vindo ao menu de seleção do SongManager!" << endl
     << "Escolha 1 para fazer uma pesquisa nas músicas cadastradas" << endl
     << "Escolha 2 para adicionar uma música ao sistema." << endl
     << "Escolha 3 para remover uma música cadastrada." << endl
     << "Escolha 0 para sair do programa." << endl;
       cout << "\nEscolha a opção desejada:" << endl;
       cin >> i;
       cin.ignore();
       switch (i) {
         case 1:
             ImprimeMenuPesquisa();
             break;
         case 2:
             cout << "Digite o nome do arquivo a ser inserido no sistema (\"nome.txt\")" << endl;
             getline(cin,entrada);
						 NovaMusica(entrada);
             break;
         case 3:
             cout << "Digite parte do titulo da musica a ser removida:" << endl;
             getline(cin,entrada);
             RemoveMusica(entrada);
             break;
         case 0:
             break;
       }
  }
}
