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
sub encontraTitulo{
	my $arquivo = $_[0];
	my ($titulo);
	
	($titulo) = ($arquivo =~ /[\n\r]Titulo:([^\n\r]*)/i);
	return ($titulo);
}

local $/=undef;
open FILE, "songs/song1.txt" or die "Couldn't open file: $!";
my $string = <FILE>;

my $data = encontraTitulo($string);
print "Titulo: $data";
close FILE;