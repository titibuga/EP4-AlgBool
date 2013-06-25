	;; EP1 DE MAC0329 - ALGEBRA BOOLEANA E SUAS APLICACOES
	;; PRIMEIRO SEMESTRE DE 2013
	;; PROFESSOR JUNIOR BARRERA
	;; GRUPO:
	;; GERVASIO PROTASIO DOS SANTOS NETO - NUSP: 7990996
	;; MATEUS BARROS RODRIGUES - NUSP: 7991037
	;; VICTOR SANCHES PORTELLA - NUSP: 7991152
	;; VINICIUS JORGE VENDRAMINI - NUSP: 7991103
	;; EP1 - PROGRAMA EM MNEMONICOS DO HIPO
	
00 {INN} 33			;le entrada de k
01 {LDA} 33			;manda k para o registrador
02 {JEQ} 32			;checa se k é menor que zero
03 {SUB} 35			;subtrai 10 de k
04 {JGT} 32			;checa se k-10 é maior ou igual a zero
	
05 {LDA} 40			;manda o contador parao acumulador
06 {SUB} 33			;subtrair o acumalador de k
07 {JGE} 26			;checa se contador - k é maior ou igual a zero

08 {INN} 34			;recebe os inputs na posicao 34
09 {LDA} 34			;manda input para acumulador
10 {SUB} 38			;faz input - menor
11 {JGE} 14			;checa se input-menor é maior ou igual a zero
12 {LDA} 34			;manda o input para o acumulador
13 {STA} 38			;manda o conteudo do contador para o endereco do menor input
14 {LDA} 34			;manda o input para acumulador
15 {SUB} 39			;faz input-maior
16 {JLE} 19			;checa se input-maior é menor ou igual a zero
17 {LDA} 34			;manda input para acumulador
18 {STA} 39			;manda conteudo do acumulador para o endereco de memoria de maior
19 {LDA} 34			;manda o input para acumulador
20 {ADD} 37			;adiciona a soma de todos os inputs ate o momento ao conteudo do acumulador
21 {STA} 37			;manda a nova soma para o endereco da soma antiga
22 {LDA} 40			;manda o contador para o acumulador
23 {ADD} 36			;adiciona 1 ao contador
24 {STA} 40			;armazena o novo valor de contador no devido endereco de memoria
25 {JMP} 05			;recomeca o loop deve continuar

26 {LDA} 37			;manda a soma para o acumulador
27 {DIV} 33			;divide a soma pelo numero de entradas
28 {STA} 37			;armazena a media aritmetica no endereco da soma

29 {PRN} 39			;exibe o maior input
30 {PRN} 38			;exibe o menor input
31 {PRN} 37			;exibe a media aritmetica

32 {STP}			;para o progrma

35 +0010			;armazena 10
36 +0001			;armazena 1
37 +0000			;armazena a soma e eventualmente a media aritmetica
38 +4999			;armazea o menor. Entradas superiores a +5000 causam Memory Overflow
39 -4999			;armazena o maior Entradas inferiores a -5000 causam Memory Overflow
40 +0000			;armazena o contador