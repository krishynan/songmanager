#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>
#include <vector>
#include "musica.h"

#define SongManagerPerl  "songmanager.pm"

using namespace std;

static PerlInterpreter *my_perl;

EXTERN_C void xs_init (pTHX);

EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);

void ObtemPesquisa (char *, char *, char *);

void ImprimeMenu();

char *ConverteStringChar (string);

void ImprimeMusica (Musica);

void RetornaMusicasArtista (vector <string>);

void BuscaArtista (string);
