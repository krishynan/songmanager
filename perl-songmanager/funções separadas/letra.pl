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
sub encontraLetra{
	my $arquivo = $_[0];
	my $trecho = $_[1];
	my $arquivoUmaLinha = $arquivo;
	
	$arquivoUmaLinha =~ tr{\n\n}{ }; #previne linhas vazias
	$arquivoUmaLinha =~ tr{\n}{ }; #previne que nao encontre pq pegou palavras em linhas diferentes
	if ($arquivoUmaLinha =~ /\sLetra:.*$trecho.*/i) {
		return ($arquivo);
	}
	return 0;
}

local $/=undef;
open FILE, "songs/song5.txt" or die "Couldn't open file: $!";
my $string = <FILE>;
my $trecho = "sometimes";

print "Procurando por:$trecho\n";
my $data = encontraLetra($string,$trecho);
if ($data) {
	print "Letra achada: $data";
}
else {
	print "Nao achou\n";
}
close FILE;