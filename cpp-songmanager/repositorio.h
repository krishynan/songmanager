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

#ifndef REPOSITORIO_H
#define REPOSITORIO_H
#include <iostream>
#include <string>
#include <vector>
#include "musica.h"
using namespace std;

class Repositorio {
 friend ostream &operator<< (ostream &, Repositorio &); //operador sobrecarregado para imprimir todos os resultados da pesquisa
 public:
 Repositorio ();

 Repositorio (const Repositorio &);

 void insereMusica (Musica &); //função para inserir uma nova musica no vetor de resultados

 void exibeMusica (int);

 Repositorio operator+ (const Repositorio &);

 private:
 vector <Musica *> vMusicas; //vetor de musicas para salvar os resultados da pesquisa
};

#endif
