#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include "musica.h"

#define SongManagerPerl  "songmanager.pm"

#ifndef DIRETORIO_DE_MUSICAS
#define DIRETORIO_DE_MUSICAS  "./songs/"
#endif

using namespace std;

static PerlInterpreter *my_perl;

EXTERN_C void xs_init (pTHX);

EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);

string InsereDiretorio (string);

void ClearScreen();

void FormataImpressao();

char *ConverteStringChar (string);

void ObtemPesquisa (char *, char *, char *);

void RetornaMusicasArtista (vector <string>);

void BuscaArtista (string);

vector <Musica> BuscaMusica (string, int);

void RetornaMusicaInteira(vector <Musica>);

bool file_exists(const char *);

void NovaMusica(string);

void RemoveMusica (string);

void ImprimeMenu();

void ImprimeMenuPesquisa();
