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

using namespace std;

static PerlInterpreter *my_perl;

EXTERN_C void xs_init (pTHX);

EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);

void ObtemPesquisa (char *, char *, char *);

void ImprimeMenuPesquisa();

void ClearScreen();

void FormataImpressao();

char *ConverteStringChar (string);

void ImprimeMusica (Musica);

void RetornaMusicasArtista (vector <string>);

void BuscaArtista (string);

vector <Musica> BuscaMusica (string, int);

void RetornaMusicaInteira(vector <Musica>);

bool file_exists(const char *);

void NovaMusica(string);

void RemoveMusica (string);

void ImprimeMenu();

string InsereDiretorio (string);
