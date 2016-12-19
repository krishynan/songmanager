/*
#   Universidade Federal do Rio de Janeiro
#   Departamento de Eletronica e de Computacao
#   Linguagens de Programacao
#
#   Trabalho 03
#
#   Grupo:
#      Krishynan Shanty
      Nicholas Quagliani
*/

#include "SongManagerAux.h"

using namespace std;
/* Funções para melhorar a estética do texto impresso na tela */
void ClearScreen () {
		int i;
		for (i=0; i<5; i++) {cout << endl;}
}

void FormataImpressao ()
{
	int i;
	for (i=0; i<10; i++) {cout << "****";}
	cout << endl;
}
/* */

/* A API do PERL requer que diversos argumentos sejam do tipo char*, essa função é chamada para realizar a conversão */
char * ConverteStringChar (string entrada)
{
	char *saida = new char[entrada.length() + 1];
	strcpy(saida, entrada.c_str());
	return saida;
}

/* Insere o diretorio definido em DIRETORIO_DE_MUSICAS ao nome do arquivo */
string InsereDiretorio (string nome_arquivo)
{
	string result;
	result = (DIRETORIO_DE_MUSICAS + nome_arquivo);
	return result;
}
/* Função para cadastrar uma nova música no diretorio de músicas */
void NovaMusica(string novoArquivo)
{
	int contador=1;
	int Arquivo_e_valido;
	char *my_argv[] = {ConverteStringChar(""), ConverteStringChar(SongManagerPerl)};
	my_perl = perl_alloc();
  perl_construct (my_perl);
  perl_parse(my_perl, xs_init, 2, my_argv, NULL);
  PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
	dSP;                      											/* Inicialização da pilha */
	ENTER;
	PUSHMARK(SP);             											/* Ponteiro para pilha */

	char *args[] = {ConverteStringChar(novoArquivo),NULL};
	call_argv("ValidaArquivo", G_DISCARD, args);																		 /* Chama a subrotina ValidaArquivo para conferir se a formatação do */
																																									 /* arquivo é valida */
	SPAGAIN;                         							 /* Atualiza o ponteiro de Pilha */

	Arquivo_e_valido = POPi;

	PUTBACK;
	FREETMPS;                        							/* libera os valores da pilha */
	LEAVE;

	perl_destruct(my_perl);
	perl_free(my_perl);

	if (!(Arquivo_e_valido))																												/* Se a formatação for válida, insere o arquivo como song#.txt */
																																									/* na pasta 'songs' */
	{
		string result;
		ostringstream conversora;
		conversora << DIRETORIO_DE_MUSICAS << "song" << contador << ".txt";
		result = conversora.str();

		while (file_exists(ConverteStringChar(result))){															/* Confere na pasta /songs/ qual a ultima musica inserida para */
																																									/* salvar a nova musica como song(#+1) 												 */
			conversora.str("");
			conversora.clear();
			conversora << DIRETORIO_DE_MUSICAS << "song" << contador << ".txt";
			result = conversora.str();
			contador++;
		}

		ifstream  arquivo_origem(ConverteStringChar(novoArquivo));
		if (arquivo_origem.is_open()) {
	  ofstream  arquivo_destino(ConverteStringChar(result));
		arquivo_destino << arquivo_origem.rdbuf();
		cout << "Musica " << novoArquivo << " adicionada com sucesso" << endl;
	  }
		else cout << "Erro ao adicionar música" << endl;

		arquivo_origem.close();
	}
	else cout << "O arquivo inserido não é válido" << endl;
}

/* Função que retorna true caso o arquivo de nome fileName já exista na pasta. */
bool file_exists(const char *fileName)
{
    ifstream infile(fileName);
    return infile.good();
}

/* Retira uma música do diretório de músicas */
void RemoveMusica (string titulo)
{
	vector <Musica> lista = BuscaMusica(titulo,1);																		/* Busca a musica a ser removida no repositório, com contexto igual a 1  */
	string decisao;																																		/* pois não é necessaria a função de exibir a música inteira nesse caso. */
	int i,indice;

	for (i = 0; i < lista.size();i++){																								/* Lista as musicas retornadas da pesquisa     */
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
	char *my_argv[] = {ConverteStringChar(""), ConverteStringChar(SongManagerPerl)};
	my_perl = perl_alloc();
  perl_construct (my_perl);
  perl_parse(my_perl, xs_init, 2, my_argv, NULL);
  PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

  if (termo2 != NULL) {																		/* Confere quantos termos foram pesquisados, para passar a */
    char *args[] = {busca,termo,termo2,NULL};							/* quantidade certa de argumentos ao programa em Perl      */
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
  if (resultados.size())																						/* Testa se a busca retornou algum valor */
	{
			for (i = 0; i < resultados.size();i++){
				cout << "Para visualizar todas as musicas do artista \"" << resultados[i] << "\" digite " << (i+1) << endl;
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
	 else {cout << "Não foram obtidos resultados para essa pesquisa" << endl;}
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
  PUSHMARK(SP);             /* Ponteiro para pilha */

	char *args[] = {ConverteStringChar("Autor"),ConverteStringChar(autor),NULL};

  call_argv("PesquisaGlobal", G_ARRAY, args);
  SPAGAIN;                         /* Atualiza o ponteiro de Pilha */

	do {
		 i++;
		 retornoPilha = POPp;
		 if (!(retornoPilha.empty())) {resultado.push_back(retornoPilha);}
	 } while(!(retornoPilha.empty()));

  PUTBACK;
  FREETMPS;                        /* libera os valores da pilha */
  LEAVE;

	perl_destruct(my_perl);
	perl_free(my_perl);

	RetornaMusicasArtista(resultado);  /* Chama a função para exibir todas as musicas dos artistas que resultaram da pesquisa */
}


/* Função que exibe o resultado da busca por musicas e imprime na tela a musica inteira*/
void RetornaMusicaInteira (vector <Musica> resultados) {
	string decisao;
	int i,indice;
	if (resultados.size())																				/* Testa se a busca retornou algum valor */
	 {
			for (i = 0; i < resultados.size();i++){
			cout << "Para exibir a letra inteira da musica \"" << resultados[i].getTitulo() << "\" digite " << (i+1) <<  endl;
		  }
			cout << "Digite 0 para voltar ao menu de pesquisa." << endl;
			cin >> indice;
			cin.ignore();
			if (indice > resultados.size())
			{
				cout << "A musica selecionada não existe!" << endl;
			}
			else if (indice == 0) {}
			else {resultados[indice-1].getMusicaInteira();}           /* Chama o método da classe Musica para imprimir a musica inteira */
		}
}


/* Realiza a busca por musicas e gera um vetor de resultados com as possiveis musicas compatíveis com a pesquisa.
	 Também chama a função RetornaMusicaInteira para o usuário visualizar a letra inteira de uma musica.
	 Recebe o inteiro escolha, que define o contexto em que a função foi chamada.
*/
vector <Musica> BuscaMusica (string musica, int escolha) {
	int i = -1;
	vector <Musica> resultados;
	Musica musicaResultante;
	string retornoPilha;

	char *my_argv[] = {ConverteStringChar(""), ConverteStringChar(SongManagerPerl)};
	my_perl = perl_alloc();
	perl_construct (my_perl);
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
  FREETMPS;                       																							/* libera os valores da pilha */
  LEAVE;

	perl_destruct(my_perl);
	perl_free(my_perl);

	if (escolha == 0) {RetornaMusicaInteira(resultados);}  												/* Se o contexto da função for de pesquisa, chama a função responsável */
																																								/* por listar os resultados e imprimir a musica inteira */

	return resultados;
}

/* Imprime o submenu para o usuário realizar uma pesquisa por Artista, Título, Data, Trecho ou Dupla
	 Também chama a função de busca correspondente com a seleção do usuário, passando o termo pesquisado para a função.
	*/
void ImprimeMenuPesquisa () {
  int i=1;
  string busca,busca2;
	ClearScreen();

		  cout << "Escolha 1 para Pesquisa por um autor. Retorna todas musicas do autor se for exato" << endl
			     << "Escolha 2 para Pesquisa por um titulo." << endl
			     << "Escolha 3 para Pesquisa por um ano de lancamento. Retorna os nomes das musicas" << endl
			     << "Escolha 4 para Pesquisa por um trecho. Retorna o titulo e um pedaco do trecho achado" << endl
			     << "Escolha 5 para Pesquisa por DOIS trechos desconectados. Retorna o titulo e um pedaco do trecho achado" << endl
			     << "Escolha 0 para voltar para o menu principal." << endl;
			 while (i != 0) {
			 FormataImpressao();
			 cout << "\nEscolha o tipo de pesquisa desejada:" << endl;
       cin >> i;
			 while(cin.fail())
			 {
			         cout << "Por favor, digite um numero" << endl;
			         cin.clear();
			         cin.ignore(256,'\n');
			         cin >> i;
			  }
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

/* Imprime o menu principal do programa */
void ImprimeMenu () {
  int i=1;
  string entrada;
	ClearScreen();
	while (i != 0) {
	FormataImpressao();
	 cout  << "Olá, bem-vindo ao menu de seleção do SongManager!" << endl
			   << "Escolha 1 para pesquisar as músicas cadastradas" << endl
			   << "Escolha 2 para listar todas as músicas de um artista." << endl
				 << "Escolha 3 para visualizar a letra completa de uma música." << endl
				 << "Escolha 4 para adicionar uma música ao sistema." << endl
			   << "Escolha 5 para remover uma música cadastrada." << endl
			   << "Escolha 0 para sair do programa." << endl;
   cout << "\nEscolha a opção desejada:" << endl;
   cin >> i;
	 while(cin.fail()) {
	         cout << "Por favor, digite um numero" << endl;
	         cin.clear();
	         cin.ignore(256,'\n');
	         cin >> i;
	    }
	  cin.ignore();
	  switch (i) {
	     case 1:
	         ImprimeMenuPesquisa();
	         break;
			 case 2:
					 cout << "Digite o artista a ser buscado:" << endl;
					 getline(cin,entrada);
					 BuscaArtista(entrada);
					 break;
			 case 3:
					 cout << "Digite o titulo a ser buscado:" << endl;
					 getline(cin,entrada);
					 BuscaMusica(entrada,0);
					 break;
			 case 4:
	         cout << "Digite o nome do arquivo a ser inserido no sistema (Formato: \"nome.txt\")" << endl;
	         getline(cin,entrada);
					 NovaMusica(entrada);
	         break;
	     case 5:
	         cout << "Digite parte do titulo da musica a ser removida:" << endl;
	         getline(cin,entrada);
	         RemoveMusica(entrada);
	         break;
	     case 0:
	         break;
	   }
 	}
}
