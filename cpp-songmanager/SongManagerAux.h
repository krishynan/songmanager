#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>

using namespace std;

static PerlInterpreter *my_perl;

EXTERN_C void xs_init (pTHX);

EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);

void ObtemPesquisa (char *, char *, char *);

void ImprimeMenu();

char *ConverteStringChar (string);
