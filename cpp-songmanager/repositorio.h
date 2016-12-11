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
 friend ostream &operator<< (ostream &, Repositorio &);

 public:
 Repositorio ();

 Repositorio (const Repositorio &);

 void insereMusica (Musica &);

 Repositorio operator+ (const Repositorio &);

 private:
 vector <Musica *> vMusicas;
};
#endif
