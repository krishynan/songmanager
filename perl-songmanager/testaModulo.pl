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

package biblioteca;
use warnings;
use strict;
use songmanager;

my ($tipoPesquisa,$procurado,$termo1);
print "Bem vindo ao Song Manager.\n";
print "A(utor)-> Pesquisa por um autor. Retorna todas musicas do autor se for exato\n";
print "T(itulo)-> Pesquisa por um titulo. Retorna a musica inteira se for exato\n";
print "L(ancamento)-> Pesquisa por um ano de lancamento. Retorna os nomes das musicas\n";
print "P(edaco)-> Pesquisa por um trecho. Retorna o titulo e um pedaco do trecho achado\n";
print "D(upla)-> Pesquisa por DOIS trechos desconectados. Retorna o titulo e um pedaco do trecho achado\n";
print "Digite por extenso ou a primeira letra da opcao desejada:\n";

$tipoPesquisa = <>;

if (!$tipoPesquisa =~ /^[atlpd]/i) {
	print "Opcao invalida";
}
if ($tipoPesquisa =~ /d/i) {
	print "Digite o primeiro trecho pra buscar:";
	chomp($procurado = <STDIN>);
	print "Digite o segundo trecho pra buscar:";
	chomp($termo1 = <STDIN>);
	PesquisaGlobal(substr($tipoPesquisa, 0, 1),substr($procurado,0,-1),substr($termo1,0,-1));
}
else {
	print "Digite o que ira buscar:";
	$procurado = <>;
	PesquisaGlobal(substr($tipoPesquisa	, 0, 1),substr($procurado,0,-1));
}
