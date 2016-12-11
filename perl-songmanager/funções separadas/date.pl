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
sub encontraData{
	my $arquivo = $_[0];
	my ($dia,$mes,$ano);
	
	($dia, $mes, $ano) = ($arquivo =~ /(\d\d)\/(\d\d)\/(\d\d\d\d)/);
	return ($dia,$mes,$ano);
}

local $/=undef;
open FILE, "songs/song1.txt" or die "Couldn't open file: $!";
my $string = <FILE>;

my @data = encontraData($string);
print "Dia: $data[0], Mes: $data[1], Ano: $data[2]";
close FILE;