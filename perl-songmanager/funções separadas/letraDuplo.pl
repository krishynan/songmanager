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
sub encontraLetraDupla{
	my $arquivo = $_[0];
	my $trecho1 = $_[1];
	my $trecho2 = $_[2];
	my $arquivoUmaLinha = $arquivo;
	
	$arquivoUmaLinha =~ tr{\n}{ };
	if ($arquivoUmaLinha =~ /\sLetra:.*$trecho1.*$trecho2.*/i) {
		return ($arquivo);
	}
	return 0;
}

local $/=undef;
open FILE, "songs/song1.txt" or die "Couldn't open file: $!";
my $string = <FILE>;
my $trecho1 = "BLA BLA";
my $trecho2 = "achei oi";

print "Procurando por:\"$trecho1\" e \"$trecho2\"\n";
my $data = encontraLetra($string,$trecho1,$trecho2);
if ($data) {
	print "Letra achada: $data";
}
else {
	print "Nao achou\n";
}
close FILE;