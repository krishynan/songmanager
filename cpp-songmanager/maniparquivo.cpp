#include "musica.h"

#define DIRETORIO_DE_MUSICAS "./songs/song"

void newMusicFile(String newFile) {
	String n_a;
	int counter=1;

	while (file_exists(n_a + DIRETORIO_DE_MUSICAS + to_string(counter) + ".txt")) counter++;

	std::ifstream  src(newFile, std::ios::binary);
    std::ofstream  dst(n_a + DIRETORIO_DE_MUSICAS + to_string(counter) + ".txt",   std::ios::binary);

    dst << src.rdbuf();

}
bool file_exists(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}
