#
#   Universidade Federal do Rio de Janeiro
#   Departamento de Eletronica e de Computacao
#   Linguagens de Programacao
#
#   Trabalho 02 - Perl para trabalhar com as letras de musica
#
#   Grupo:
#      Krishynan Shanty
#      Nicholas Quagliani

use warnings;
use strict;
sub encontraAutor{
	my $arquivo = $_[0];
	my ($autor);
	
	($autor) = ($arquivo =~ /^Autor:([^\n\r]*)/i)	;
	return ($autor);
}

local $/=undef;
open FILE, "songs/song1.txt" or die "Couldn't open file: $!";
my $string = <FILE>;

my $data = encontraAutor($string);
print "Autor: $data";
close FILE;