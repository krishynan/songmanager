#include "repositorio.h"

ostream &operator<< (ostream &out, Repositorio &r) { //operador sobrecarregado para imprimir todos os resultados da pesquisa
 for (int i = 0; i < r.vMusicas.size (); i++) {
 ((r.vMusicas).at (i))->print ();
 }
 return out;
}

Repositorio::Repositorio () {}
Repositorio::Repositorio (const Repositorio &r) {
 vMusicas = r.vMusicas;
}
