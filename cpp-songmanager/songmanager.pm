#package songmanager;
#package biblioteca;

use 5.014002;
use strict;
use warnings;
use Carp;


require Exporter;

our @ISA = qw(Exporter);

# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.

# This allows declaration	use songmanager ':all';
# If you do not need this, moving things directly into @EXPORT or @EXPORT_OK
# will save memory.
our %EXPORT_TAGS = ( 'all' => [ qw(ValidaArquivo EncontraAutor EncontraTitulo EncontraData EncontraLetra EncontraLetraDupla PesquisaGlobal
) ] );

#our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );
our @EXPORT_OK = qw( ValidaArquivo EncontraAutor EncontraTitulo EncontraData EncontraLetra EncontraLetraDupla PesquisaGlobal );
our @EXPORT = qw(
);

our $VERSION = '0.03';

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

sub EncontraData{
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
my @titulos_E_Arquivos;
$achados = "";

	foreach my $arquivos (glob("songs/*.txt")) {
		open FILE, $arquivos or die "Couldn't open file: $!";
		my $arquivo = do {local $/; <FILE>};

		if (!ValidaArquivo($arquivo)){
			if ($tipoPesquisa =~ /^a(?:utor)?/i) {
				$atual = EncontraAutor($arquivo);
				if ($atual=~ /^$procurado$/i) {   #se for exato,devolve todas musicas que forem com o autor exato
					$achados .= "Musica dele:";
					$achados .= EncontraTitulo($arquivo);
					$achados .= "\n";
					push @titulos_E_Arquivos, $atual;
				}
				else {
					if ($atual =~ /[\w\s]*$procurado[\w\s]*/i) {  #se nao for exato mas ainda acha
						if (!($achados =~ /[\w\s]*$atual[\w\s]*/i)){  #confere se ja nao sugeriu esse artista antes
							$achados .= "Artista possivel:$atual\n";
							push @titulos_E_Arquivos, $atual;
						}
					}
				 }
			}
			if ($tipoPesquisa =~ /^t(?:itulo)?/i) {
				$atual = EncontraTitulo($arquivo);
					if ($atual =~ /[\w\s]*$procurado[\w\s]*/i) {  #nao exato retorna o titulo
						$achados .= "Musica possivel:$atual\n";
						push @titulos_E_Arquivos, $atual;
						push @titulos_E_Arquivos, $arquivos;
					}
			}
			if ($tipoPesquisa =~ /^p(?:edaço)?/i) {
				$atual = EncontraLetra($arquivo,$procurado);
				if ($atual) {
					$achados .= "Musica:";
					$achados .= EncontraTitulo($arquivo);
					$achados .= "\nTrecho:\n$atual\n";
					push @titulos_E_Arquivos, $atual;
					push @titulos_E_Arquivos, $arquivos;
				}
			}
			if ($tipoPesquisa =~ /^d(?:upla)?/i) {
				$atual = EncontraLetraDupla($arquivo,$procurado,$termo1);
				if ($atual) {
					$achados .= "Musica:";
					$achados .= EncontraTitulo($arquivo);
					$achados .= "\nTrecho:\n$atual\n";
					push @titulos_E_Arquivos, $atual;
					push @titulos_E_Arquivos, $arquivos;
				}
			}
			if ($tipoPesquisa =~ /^L(?:ançamento)?/i) {
				($dia,$mes,$ano) = EncontraData($arquivo);#nao uso o dia e o mes pra nada ainda, fica pro futuro
				if ($procurado eq $ano) {
					$achados .= EncontraTitulo($arquivo);
					$achados .= "\n";
					push @titulos_E_Arquivos, $atual;
					push @titulos_E_Arquivos, $arquivos;
				}
			}
		}
	}
	print $achados;
	return @titulos_E_Arquivos;
}
# Preloaded methods go here.

# Autoload methods go after =cut, and are processed by the autosplit program.

1;
__END__

=head1 NAME

songmanager - Perl extension for functions that analyze and search lyrics on text files

=head1 SYNOPSIS

  use songmanager;

=head1 DESCRIPTION
	Analyze lyrics using this template:

	Autor:Author
	Titulo:Title
	Letra:Type the lyrics here
	It accepts new line

	Up to one empty line
	Thanks

=head2 EXPORT

None by default.

=head1 AUTHOR

Krishynan, E<lt>krishynan@poli.ufrj.brE<gt>

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2016 by Krishynan,Nicholas

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.24.0 or,
at your option, any later version of Perl 5 you may have available.


=cut
