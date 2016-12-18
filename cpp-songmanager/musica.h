#ifndef MUSICA_H
#define MUSICA_H
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

#define DIRETORIO_DE_MUSICAS "./songs/"

using namespace std;

class Musica {

 public:
 Musica ();
 Musica (string, string, string ); // construtor para Titulo, Autor e Nome do arquivo
 Musica (string, string, string, string ); // construtor para Titulo, Autor, Trecho e Nome do arquivo
 Musica (string, string, string, string, string ); // construtor para Titulo, Autor, Trecho, Data e Nome do arquivo

 string getTitulo ();
 string getAutor ();
 string getData ();
 string getTrecho ();
 char *getNomeArquivo();    //retorna um char * para abrir o arquivo

 void setAutor(string);
 void setTitulo(string);
 void setNomeArquivo(char *);
// void setTitulo ();

 void getMusicaInteira();

 void print ();

 private:

 string Titulo, Autor, Data, Trecho;
 string NomeArquivo;
};


#endif
