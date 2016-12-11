#ifndef MUSICA_H
#define MUSICA_H
#include <iostream>
#include <string>
using namespace std;

class Musica {
 public:


 Musica (string, string, string); // construtor para Titulo, Autor e Nome do arquivo
 Musica (string, string, string, string); // construtor para Titulo, Autor, Trecho e Nome do arquivo
 Musica (string, string, string, string, string); // construtor para Titulo, Autor, Trecho, Data e Nome do arquivo

 string getTitulo ();
 string getAutor ();
 string getData ();
 string getTrecho ();

// void setTitulo ();

 string getMusicaInteira();

 void print ();

 private:

 string Titulo, Autor, Data, Trecho, NomeArquivo;

};


#endif
