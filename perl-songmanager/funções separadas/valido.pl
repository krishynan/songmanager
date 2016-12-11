#
#   Universidade Federal do Rio de Janeiro
#   Departamento de Eletronica e de Computacao
#   Linguagens de Programacao
#
#   Trabalho 02 - Perl para trabalhar com as letras de música
#
#   Grupo:
#      Krishynan Shanty
#      Nicholas Quagliani

use warnings;
use strict;

sub validaArquivo{
	my $arquivo = $_[0];
	
	if ($arquivo =~ /\n{3,}/) {   #só pode ter 1 linha vazia no maximo
		return 1;
	}
	if ($arquivo =~ / {2,}/) {   #nao pode ter espaco repetido
		return 2;
	}
	if ($arquivo =~ /^Autor:[\w']+\s?(?:[\w']+\s?)*\w+\nTitulo:[\w']+\s?(?:[\w']+\s?)*[\w']+\n\d\d\/\d\d\/\d\d\d\d\nLetra:[\w',.\(\)!?]+\s?(?:(?:[\w',.]+\s)*\n?)*[\w',.]+/) {
		return 0;  #regex gigante que cobra pelo menos uma palavra em cada campo,nao permite terminar em espaco,etc
	}
	return 3;
}

my @arquivos = <songs/*.txt>;
foreach my $arquivos (@arquivos) {
	open FILE, $arquivos or die "Couldn't open file: $!";
	my $arquivo = do {local $/; <FILE>};
	
	if (!validaArquivo($arquivo)) {
		print "$arquivos valido\n";
	}
	else {
		print "$arquivos invalido\n";
	}
	
	
}