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
	my $trechoCompleto;
	my $aux;

	$arquivoUmaLinha =~ tr{\n\n}{ };
	$arquivoUmaLinha =~ tr{\n}{ };
	if ($arquivoUmaLinha =~ /\sLetra:.*($trecho1(.*)$trecho2).*/i) {
		print length ($2);
		if (length ($2) < 40) {      #envia o trecho entre as palavras procuradas se nao for grande
			return $1;
		}
		($trechoCompleto) = $arquivoUmaLinha =~ /((?:['\w]+(?:,?\s)){0,6}$trecho1(?:(?:,?\s)['\w]+){0,6})/i; #se nao procura ate mais 7 palavras entre o trecho
		$trechoCompleto .= " (...) ";
		($aux) = $arquivoUmaLinha =~ /((?:['\w]+(?:,?\s)){0,6}$trecho2(?:(?:,?\s)['\w]+){0,6})/i;
		$trechoCompleto .= $aux;
		return $trechoCompleto;
	}
	return 0;
}

sub encontraAutor{
	my $arquivo = $_[0];
	my ($autor);

	($autor) = ($arquivo =~ /^Autor:([^\n\r]*)/i);
	return $autor;
}

sub encontraTitulo{
	my $arquivo = $_[0];
	my ($titulo);

	($titulo) = ($arquivo =~ /[\n\r]Titulo:([^\n\r]*)/i);
	return $titulo;
}

sub encontraLetra{
	my $arquivo = $_[0];
	my $trecho = $_[1];
	my $arquivoUmaLinha = $arquivo;
	my $trechoCompleto;

	$arquivoUmaLinha =~ tr{\n\n}{ };
	$arquivoUmaLinha =~ tr{\n}{ };
	if ($arquivoUmaLinha =~ /\sLetra:(.*$trecho.*)/i) {
		($trechoCompleto) = $1 =~ /((?:['\w]+(?:,?\s)){0,10}$trecho(?:(?:,?\s)['\w]+){0,10})/i; #regex bolado pra copiar um trecho com ate 10 palavras ao redor da palavra achada PODENDO TER VIRGULA
		return $trechoCompleto;
	}
	return 0;
}

sub encontraData{
	my $arquivo = $_[0];
	my ($dia,$mes,$ano);

	($dia, $mes, $ano) = ($arquivo =~ /(\d\d)\/(\d\d)\/(\d\d\d\d)/);
	return ($dia,$mes,$ano);
}

sub pesquisaGlobal{
my $tipoPesquisa = $_[0];
my $procurado = $_[1];
my $termo1 = $_[2];
my @arquivos = <songs/*.txt>;
my ($achados,$atual,$dia,$mes,$ano);
$achados = "";
	foreach my $arquivos (@arquivos) {
		open FILE, $arquivos or die "Couldn't open file: $!";
		my $arquivo = do {local $/; <FILE>};

		if ($tipoPesquisa =~ /a(?:utor)?/i) {
			$atual = encontraAutor($arquivo);
			if ($atual=~ /^$procurado$/i) {
				$achados .= "Musica dele:";
				$achados .= encontraTitulo($arquivo);
				$achados .= "\n";
			}
			else {
				if ($atual =~ /[\w\s]*$procurado[\w\s]*/i) {
					if (!($achados =~ /[\w\s]*$atual[\w\s]*/i)){
						$achados .= "Artista possivel:$atual\n";
					}
				}
			}
		}
		if ($tipoPesquisa =~ /t(?:itulo)?/i) {
			$atual = encontraTitulo($arquivo);
			if ($atual=~ /^$procurado$/i) {
				$achados .= $arquivo;
				$achados .= "\n";
			}
			else {
				if ($atual =~ /[\w\s]*$procurado[\w\s]*/i) {
					$achados .= "Musica possivel:$atual\n";
				}
			}
		}
		if ($tipoPesquisa =~ /p(?:edaço)?/i) {
			$atual = encontraLetra($arquivo,$procurado);
			if ($atual) {
				$achados .= "Musica:";
				$achados .= encontraTitulo($arquivo);
				$achados .= "\nTrecho:\n$atual\n";
			}
		}
		if ($tipoPesquisa =~ /d(?:upla)?/i) {
			$atual = encontraLetraDupla($arquivo,$procurado,$termo1);
			if ($atual) {
				$achados .= "Musica:";
				$achados .= encontraTitulo($arquivo);
				$achados .= "\nTrecho:\n$atual\n";
			}
		}
		if ($tipoPesquisa =~ /L(?:ançamento)?/i) {
			($dia,$mes,$ano) = encontraData($arquivo);#nao uso o dia e o mes pra nada ainda, fica pro futuro
			if ($procurado==$ano) {
				$achados .= encontraTitulo($arquivo);
				$achados .= "\n";
			}
		}
	}

	if ($tipoPesquisa =~ /d(?:upla)?/i) {
		print "Procurou por: \"$procurado\" e \"$termo1\"\n";
	}
	else {
		print "Procurou por: $procurado\n";
	}
	print "$achados";
}

# pesquisaGlobal("p","WALK");
