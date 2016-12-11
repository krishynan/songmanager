#include "musica.h"

Musica::Musica (string t, string a, string n_a) : Titulo (t), Autor (a), NomeArquivo (n_a) {}

Musica::Musica (string t, string a, string tr, string n_a) : Titulo (t), Autor (a), Trecho (tr), NomeArquivo (n_a) {}

Musica::Musica (string t, string a, string tr, string d, string n_a) : Titulo (t), Autor (a), Trecho (tr), Data (d), NomeArquivo (n_a) {}

string Musica::getAutor() {return Autor;}
string Musica::getTitulo() {return Titulo;}
string Musica::getData() {return Data;}
string Musica::getTrecho() {return Trecho;}
string Musica::getNomeArquivo () {return NomeArquivo;}

void Musica::print() {
  cout << getTitulo () << "\t" <<
  getAutor () << "\t" <<
  getNomeArquivo () << endl;
}
/*
string Musica::getMusicaInteira() { //Imprime a Letra inteira da música, pesquisando o nome do arquivo na pasta e abrindo-o

} */
