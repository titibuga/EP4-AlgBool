/**********************************************************************************************
 EP1 DE MAC0329 - ALGEBRA BOOLEANA E SUAS APLICACOES
 PRIMEIRO SEMESTRE DE 2013

 PROFESSOR: JUNIOR BARRERA

 GRUPO:

 GERVASIO PROTASIO DOS SANTOS NETO - NUSP:7990996
 VINICIUS JORGE VENDRAMINI - NUSP: 7991103
 MATEUS BARROS RODRIGUES - NUSP: 7991037
 VICTOR SANCHES PORTELLA - NUSP: 7991152

 EP1 - MONTADOR
 ***********************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100
#define SINTAX_ERROR -1

/*Variáveis Globais */

char* prefixo;



/*---------------- Protótipos das funções ---------------------*/
void cleanBuffer(char buffer[]);
void * mallocSafe(size_t n);
char* verifSintaxe(char linha[]);
void erroSintaxe(char prog_name[]);

/*------------------------------------------------------------*/



int main(int argc, char* argv[]){
    FILE *entrada, *saida; /*ponteiros para os arquivos de entrada e de saida*/
    int size, linhaC = 0, i, linha = 0, linhaAux = -1;
    char *arquivoSaida, *buffer, comando[6], mnemonico[4]; /*nomes dos arquivos e um buffer, a ser usado para armazenar os caracteres contidos no arquivoFonte e a traducao do comando*/


    printf("Nome do arquivo de entrada: %s\n", argv[1]);
    size = strlen(argv[1]);

    entrada = fopen(argv[1], "r");

    if( entrada == NULL ){
        printf("Nao foi possivel ler o arquivo de entrada\n");
        exit(-1);
    } /*encerra o programa caso o arquivo passado como argumento nao exista*/

    else printf("Arquivo lido com sucesso.\n");

    /*constroi o nome do arquivo de saida baseando-se no nome do arquivo de entrada do formato nomeDoArquivo.asm*/

    arquivoSaida = mallocSafe(strlen(argv[1])+1);
    prefixo = mallocSafe(size);
    strcpy(arquivoSaida,argv[1]);


    arquivoSaida[size-4] = '\0';
    strcpy(prefixo,arquivoSaida);

    arquivoSaida = strcat(arquivoSaida,".~hip");

    saida = fopen(arquivoSaida, "w"); /*abre o arquivo de saida para escrita*/


    buffer = mallocSafe(BUFFER_SIZE);
    cleanBuffer(buffer);


    while( fgets(buffer, BUFFER_SIZE,entrada)!= NULL ){ /*le strings do arquivo de entrada ate encontrar o final do arquivo*/
        /*buffer[ 0] e buffer[1] sao o endereco de memoria*/
        /*se ha algo depois de buffer[10] sao, teoricamente, comentarios*/
        /*vamos assumir que mnemonicos comecam com o caracter '{'*/


      buffer = verifSintaxe(buffer);
      if (!buffer)
      {
        buffer = mallocSafe(BUFFER_SIZE);
        cleanBuffer(buffer);
        continue;
      }

      /*linhaAux = linha;*/ 
      if (buffer[0]>= '0' && buffer[0]<='9' && buffer[1]>= '0' && buffer[1]<='9') {
	linha = atoi(&buffer[0]);
	linhaC++;
      }
      
      if(linha <= linhaAux) erroSintaxe(prefixo); /*Impede conflito de endereço de memória*/
      linhaAux = linha;
      
      
      while(linhaC < linha){
	fprintf(saida,"\n");
	linhaC++;
      }
      
        if( buffer[3] == '+' || buffer[3] == '-' ){
	  
	  for(i = 0; i < 5; i++) /*copia o numero a ser inserido no codigo de maquina para uma string auxiliar, a ser impressa no arquivo de saida*/
	    comando[i] = buffer[3+i];
            comando[5] = '\0'; /*marca o final da string contendo o comando/numero em codigo de maquina. Usado para impedir overflow.*/
	    
            fprintf(saida, "%s\n", comando);
        }
	
        else if( buffer[3] == '{' ){
	  
	  for(i = 0; i < 3; i++) /*extrai da linha de codigo o mnemonico utilizado para que o codigo correspondete possa ser impresso no arquivo de saida*/
	    mnemonico[i] = buffer[4+i];
            mnemonico[3] = '\0'; /*marca o final da string contendo o mnemico. Impede overflow*/
            comando[5] = '\0'; /*Idem*/
	    
            /*Os condicionais a seguir comparam o mnemonico extraido com a lista de mnemonicos do HIPO e colocam em um string auxliar, a ser impressa no arquivo .hip, o codigo correspondente*/
	    
            if(strcmp(mnemonico, "LDA") == 0){
	      comando[0] = '+';
	      comando[1] = '1';
	      comando[2] = '1';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];
	      
	      fprintf(saida, "%s\n", comando);
            }
	    
            else if(strcmp(mnemonico, "STA") == 0){
	      comando[0] = '+';
	      comando[1] = '1';
	      comando[2] = '2';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];
	      
	      fprintf(saida, "%s\n", comando);
            }
	    
            else if(strcmp(mnemonico, "ADD") == 0){
	      comando[0] = '+';
	      comando[1] = '2';
	      comando[2] = '1';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];
	      
	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "SUB") == 0){
	      comando[0] = '+';
	      comando[1] = '2';
	      comando[2] = '2';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "MUL") == 0){
	      comando[0] = '+';
	      comando[1] = '2';
	      comando[2] = '3';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "DIV") == 0){
	      comando[0] = '+';
	      comando[1] = '2';
	      comando[2] = '4';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "REM") == 0){
	      comando[0] = '+';
	      comando[1] = '2';
	      comando[2] = '5';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "REV") == 0){
	      comando[0] = '+';
	      comando[1] = '2';
	      comando[2] = '9';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "INN") == 0){
	      comando[0] = '+';
	      comando[1] = '3';
	      comando[2] = '1';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "PRN") == 0){
	      comando[0] = '+';
	      comando[1] = '4';
	      comando[2] = '1';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "NOP") == 0){
	      comando[0] = '+';
	      comando[1] = '5';
	      comando[2] = '0';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "JMP") == 0){
	      comando[0] = '+';
	      comando[1] = '5';
	      comando[2] = '1';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "JLE") == 0){
	      comando[0] = '+';
	      comando[1] = '5';
	      comando[2] = '2';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "JDZ") == 0){
	      comando[0] = '+';
	      comando[1] = '5';
	      comando[2] = '3';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "JGT") == 0){
	      comando[0] = '+';
	      comando[1] = '5';
	      comando[2] = '4';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "JEQ") == 0){
	      comando[0] = '+';
	      comando[1] = '5';
	      comando[2] = '5';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "JLT") == 0){
	      comando[0] = '+';
	      comando[1] = '5';
	      comando[2] = '6';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "JGE") == 0){
	      comando[0] = '+';
	      comando[1] = '5';
	      comando[2] = '7';
	      comando[3] = buffer[9];
	      comando[4] = buffer[10];

	      fprintf(saida, "%s\n", comando);
            }

            else if(strcmp(mnemonico, "STP") == 0){
	      comando[0] = '+';
	      comando[1] = '7';
	      comando[2] = '0';
	      comando[3] = '0';
	      comando[4] = '0';

	      fprintf(saida, "%s\n", comando);
            }

            else erroSintaxe(prefixo);
        }
	else erroSintaxe(prefixo);

	cleanBuffer(buffer);
    }


    strcat(prefixo,".hip");
    if (rename(arquivoSaida,prefixo)){
      printf("Erro: Problema ao tentar renomear o arquivo temporário.\n");
      exit(-1);
    }


    fclose(entrada); /*fecha arquivo de entrada*/

    printf("Arquivo em 'codigo-maquina' salvo em %s.\n", prefixo);

    return 0;
}

/* ********************************************
   O método cleanBuffer coloca em todas as posições do vetor
   de caracteres o caracter '\0'
   ********************************************** */

void cleanBuffer(char buffer[]){
  int i = 0;
  for(i = 0; i < sizeof(buffer); i++)
    buffer[i] = '\0';
}


/* ********************************************
   A função mallocSafe aloca n Bytes da memória, e caso não seja possível
   alocar essa quantidade de memória, solta uma mensgaem de erro e finaliza
   o programa.
   ********************************************** */
void * mallocSafe(size_t n)
{
  void * pt;
  pt = malloc(n);
  if (pt == NULL) {
    printf("ERRO na alocacao de memoria.\n\n");
    exit(-1);
  }
  return pt;
}


/* ********************************************
   A função verifSintaxe pega uma linha e verifica se está de acordo
   com a sintaxe do HIPO, e retorna uma string onde:

   Carateres 0 e 1 são o endereço de memória
   Caracteres 3,4,5,6 e 7 são ou o Mnemonico do comando ou um número de 4 digitos com sinal.
   Caracteres 9 e 10 são um número, caso os caracteres anteriores fossem um mnemonivo.

   Caso haja erro de sintaxe, é chamado o método erroSintaxe();
   ********************************************** */

char* verifSintaxe(char *linha)
{
  char *final, *temp;
  int i, n = 0;

  temp = NULL;
  final = mallocSafe(12);


  if(!linha) return NULL;
  while(*linha == ' ' || *linha == '\t') linha++;
  if(*linha == '\n' || *linha == EOF || *linha == ';') return NULL; /*Linha vazia*/


  for(i=0; i<11; i++) final[i] = ' ';
  final[11]='\0';

  while(*linha !='\n' && *linha != EOF && *linha != '\0')
    {
      if (*linha == ';') break; /*Comentário*/

      switch (n)
	{
	  /*Primeira palavra: endereço de memória*/
	case 0:


	  if(temp) free(temp);
	  temp = mallocSafe(3);
	  i=0;
	  while( (*linha<='9' && *linha >= '0') && i<=1 )
	    {
	      temp[i++] = *linha;
	      linha++;
	    }

	  /*Caso o endereço de memória contanha mais do que 2 caracteres juntos é erro de sintaxe,
	    por a memória estra entre 0 e 99*/
	  if (*linha != ' ') erroSintaxe(prefixo);

	  if( i == 1 )
	    {
	      final[0]='0';
	      final[1]= temp[0];
	    }
	  else for (i=0; i<=1; i++) final[i] = temp[i];
	  n++;
	  break;


	  /*Segunda palavra: Comando ou valor para se guardar na memória */
	case 1:

	  if(*linha == '+' || *linha == '-') /*Valor a ser guardado */
	    {
	      final[3]=*linha;
	      linha++;
	      for(i=0; i<=3; i++)
		{
		  if( (final[4+i]= *linha)>'9' || final[4+i]<'0' ) /* Valor tem que ser numérixo */
		    erroSintaxe(prefixo);
		  linha++;
		}

	      /*Se tiver qualque coisa após esse valor, tem que ser comentário, se não é erro de Sintaxe.
		Caso haja algo que nao seja comentário, cairá no caso Default */
	      n = 3;
	    }

	  else if(*linha == '{')
	    {
	      final[3] =  *linha;
	      linha++;
	      while(*linha == ' ') linha++;
	      for(i=0; i<3; i++)
		{
		  if( (final[4+i]=*linha)<'A' || final[4+i]>'Z') /* Comando deve ter somente letras*/
		    erroSintaxe(prefixo);
		  linha++;
		}
	      n++;

	      /*Agora verificar se existe o fechamento das chaves '}' */
	      while(*linha == ' ') linha++;
	      if( (final[7]=*linha) != '}' ) erroSintaxe(prefixo);
	      linha++;


	    }
	  else erroSintaxe(prefixo);
	  break;


	   /*Terceira palavra: Só existe se a anterior era um comando, e tem que ser um número de 2 dígitos*/
	case 2:
	  for(i=0 ; i<2; i++)
	    {
	      if( (final[9+i] = *linha) < '0' || final[9+i] > '9' )
		erroSintaxe(prefixo);
	      linha++;
	    }
	  n++;
	  break;

	  /*Entra nesse caso somente se for encontrada uma palavra que não condiz com a sintaxe do HIPO*/
	default:
	  erroSintaxe(prefixo);
	  break;
	}

      while(*linha == ' ' || *linha == '\t') linha++;

    }

  return final;

}



/* ********************************************
   O método erroSintaxe lança uma mensagem avisando sobre o erro de sintaxe,
   deleta o arquivo temporário e finaliza o programa
   ********************************************** */


void erroSintaxe(char prog_name[]){
  fprintf(stdout, "Erro de sintaxe.\n");
  prog_name[strlen(prog_name)-4]= '\0';
  remove(strcat(prog_name,".~hip"));
  exit(SINTAX_ERROR);
}

