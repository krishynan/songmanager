#include "musica.h"
#include <string>

Musica::Musica () {}

Musica::Musica (string t, string a, string n_a) : Titulo (t), Autor (a), NomeArquivo (n_a) {}

Musica::Musica (string t, string a, string tr, string n_a) : Titulo (t), Autor (a), Trecho (tr), NomeArquivo (n_a) {}

Musica::Musica (string t, string a, string tr, string d, string n_a) : Titulo (t), Autor (a), Trecho (tr), Data (d), NomeArquivo (n_a) {}

void Musica::setAutor(string a) {Autor = a;}
void Musica::setTitulo(string t) {Titulo = t;}
void Musica::setNomeArquivo(char *n_a) {NomeArquivo = n_a;}

string Musica::getAutor() {return Autor;}
string Musica::getTitulo() {return Titulo;}
string Musica::getData() {return Data;}
string Musica::getTrecho() {return Trecho;}
char *Musica::getNomeArquivo() {
  char *Nome_Arquivo = new char[NomeArquivo.length() + 1];
	strcpy(Nome_Arquivo, NomeArquivo.c_str());
	return Nome_Arquivo;
  }

void Musica::print() {
  cout << getTitulo () << "\t" <<
  getAutor () << "\t" <<
  getNomeArquivo () << endl;
}

void Musica::getMusicaInteira() { //Imprime a Letra inteira da música, pesquisando o nome do arquivo na pasta e abrindo-o
    string novaLinha;
    ifstream meuArquivo (getNomeArquivo());
    if (meuArquivo.is_open())
    {
      while ( getline(meuArquivo,novaLinha))
      {
        cout << novaLinha << endl;
      }
      meuArquivo.close();
    }
    else cout << "Unable to open file" << endl;
}
