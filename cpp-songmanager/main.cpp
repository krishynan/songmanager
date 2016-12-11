#include <iostream>
#include <string>
#include <vector>
#include "musica.h"
#include "repositorio.h"

using namespace std;

int main () {
  Repositorio repositorio;
  Musica musica1("Hello", "Adele", "Hello_Adele.mp3");
  Musica musica2("Rolling in the Deep",
  "Adele",
  "There's a fire starting in my heart Reaching a fever pitch, and it's bringing me out the dark"
  ,"Rolling in the Deep_Adele.mp3");
  repositorio.insereMusica(musica1);
  repositorio.insereMusica(musica2);

  cout << "Depois das inserções" << endl;
  cout << repositorio <<endl;

  return 0;

}
