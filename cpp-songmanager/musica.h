#ifndef MUSICA_H
#define MUSICA_H
#include <iostream>
#include <string>
using namespace std;

class Musica {
 public:

 Musica (string, string, string);

 string getTitulo ();
 string getAutor ();
 string getData ();
 string getLetra ();

// void setTitulo ();

 string getMusicaInteira();

 void print ();

 private:

 string Titulo, Autor, Data, Letra, NomeArquivo;

};


#endif
