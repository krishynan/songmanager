use strict;
use warnings;

our $VERSION = '0.01';

sub ValidaArquivo{
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

sub EncontraAutor{
	my $arquivo = $_[0];
	my ($autor);

	($autor) = ($arquivo =~ /^Autor:([^\n\r]*)/i);
	return $autor;
}

sub EncontraTitulo{
	my $arquivo = $_[0];
	my ($titulo);

	($titulo) = ($arquivo =~ /[\n\r]Titulo:([^\n\r]*)/i);
	return $titulo;
}

sub encontraData{
	my $arquivo = $_[0];
	my ($dia,$mes,$ano);

	($dia, $mes, $ano) = ($arquivo =~ /(\d\d)\/(\d\d)\/(\d\d\d\d)/);
	return ($dia,$mes,$ano);
}

sub EncontraLetra{
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

sub EncontraLetraDupla{
	my $arquivo = $_[0];
	my $trecho1 = $_[1];
	my $trecho2 = $_[2];
	my $arquivoUmaLinha = $arquivo;
	my $trechoCompleto;
	my $aux;

	$arquivoUmaLinha =~ tr{\n\n}{ };
	$arquivoUmaLinha =~ tr{\n}{ };
	if ($arquivoUmaLinha =~ /\sLetra:.*($trecho1(.*)$trecho2).*/i) {
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

sub PesquisaGlobal{
my $tipoPesquisa = $_[0];
my $procurado = $_[1];
my $termo1 = $_[2];
my ($achados,$atual,$dia,$mes,$ano);
$achados = "";

	foreach my $arquivos (glob("songs/*.txt")) {
		open FILE, $arquivos or die "Couldn't open file: $!";
		my $arquivo = do {local $/; <FILE>};

		if (!ValidaArquivo($arquivo)){
			if ($tipoPesquisa =~ /a(?:utor)?/i) {
				$atual = EncontraAutor($arquivo);
				if ($atual=~ /^$procurado$/i) {   #se for exato,devolve todas musicas que forem com o autor exato
					$achados .= "Musica dele:";
					$achados .= EncontraTitulo($arquivo);
					$achados .= "\n";
				}
				else {
					if ($atual =~ /[\w\s]*$procurado[\w\s]*/i) {  #se nao for exato mas ainda acha
						if (!($achados =~ /[\w\s]*$atual[\w\s]*/i)){  #confere se ja nao sugeriu esse artista antes
							$achados .= "Artista possivel:$atual\n";
						}
					}
				}
			}
			if ($tipoPesquisa =~ /t(?:itulo)?/i) {
				$atual = EncontraTitulo($arquivo);
				if ($atual=~ /^$procurado$/i) {  #exato mostra a musica inteira
					$achados .= $arquivo;
					$achados .= "\n";
				}
				else {
					if ($atual =~ /[\w\s]*$procurado[\w\s]*/i) {  #nao exato retorna o titulo
						$achados .= "Musica possivel:$atual\n";
					}
				}
			}
			if ($tipoPesquisa =~ /p(?:edaço)?/i) {
				$atual = EncontraLetra($arquivo,$procurado);
				if ($atual) {
					$achados .= "Musica:";
					$achados .= EncontraTitulo($arquivo);
					$achados .= "\nTrecho:\n$atual\n";
				}
			}
			if ($tipoPesquisa =~ /d(?:upla)?/i) {
				$atual = EncontraLetraDupla($arquivo,$procurado,$termo1);
				if ($atual) {
					$achados .= "Musica:";
					$achados .= EncontraTitulo($arquivo);
					$achados .= "\nTrecho:\n$atual\n";
				}
			}
			if ($tipoPesquisa =~ /L(?:ançamento)?/i) {
				($dia,$mes,$ano) = EncontraData($arquivo);#nao uso o dia e o mes pra nada ainda, fica pro futuro
				if ($procurado==$ano) {
					$achados .= EncontraTitulo($arquivo);
					$achados .= "\n";
				}
			}
		}
	}
	print $achados;
}
