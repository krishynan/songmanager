#include "menu.h"

using namespace std;

/* Opcão 1 do Menu de Seleção */
void menuOpcao1 (string autor) {
    cout << "Resultado da busca por autor: " << autor << endl;
}

/* Opcão 2 do Menu de Seleção */
void menuOpcao2 (string titulo) {
    cout << "Resultado da busca por titulo: " << titulo << endl;
}

/* Opcão 3 do Menu de Seleção */
void menuOpcao3 (string data) {
    cout << "Resultado da busca por data: " << data << endl;
}

/* Opcão 4 do Menu de Seleção */
void menuOpcao4 (string trecho) {
    cout << "Resultado da busca por trecho: " << trecho << endl;
}

/* Opcão 5 do Menu de Seleção */
void menuOpcao5 (string busca1, string busca2) {
    cout << "Resultado da busca por trecho duplo: " << busca1 << "\t" << busca2 << endl;
}
