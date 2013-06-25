#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define STRINGMAX 80

int main (int argc, char *argv[]) {
    
    /*
     Declarações
    */
    
    FILE *entrada = NULL;
    FILE *saida = NULL;
    
    char *palavra = malloc(STRINGMAX * sizeof(char));
    char *comando = malloc(5 * sizeof(char));
    
    fpos_t *aux = malloc(sizeof(fpos_t));
    
    int linhaAnt = 0;
    int linha = 0;
    int numero = 0;
    
    
    
    
    /*
     Abertura de arquivos
    */
    
    entrada = fopen(argv[1], "r");
    
    if(entrada == NULL ){
        printf("Nao foi possivel ler o arquivo de entrada\n");
        exit(-1);
    } /*encerra o programa caso o arquivo passado como argumento nao exista*/
    
    saida = fopen("saida.hip", "w");
    
    fgetpos(entrada, aux);
    
    
    
    
    /*
     Processamento do arquivo
    */
    
    
    while (!feof(entrada)) {
        
        /* Leitura do número da linha */
        fscanf(entrada, "%s", palavra);
        if (palavra[0] == ';') {
            while (fgetc(entrada) != '\n');
            continue;
        }
        
        linha = atoi(palavra);
        
        while (linhaAnt++ < linha) fprintf(saida, "0000 ");
        
        /* Lê a segunda palavra, que pode ser um número ou um comando */
        fscanf(entrada, "%s", palavra);     /* Checa comentário */
        if (palavra[0] == ';') {
            while (fgetc(entrada) != '\n');
            continue;
        }
        
        if (palavra[0] == '-' || palavra[0] == '+') {   /* Se for um número */
            numero = atoi(palavra);
            fprintf(saida, "%d ", numero);
            continue;
        }
        else {          /* Se for um comando */
            comando = ++palavra;
            comando[3] = '\0';
                        
            if(strcmp(comando, "LDA") == 0)
                fprintf(saida, "0B");
            else if(strcmp(comando, "STA") == 0)
                fprintf(saida, "0C");
            else if(strcmp(comando, "INN") == 0)
                fprintf(saida, "1F");
            else if(strcmp(comando, "PRN") == 0)
                fprintf(saida, "29");
            else if(strcmp(comando, "STP") == 0) {
                fprintf(saida, "4600 ");
                continue;
            }
            
            else if(strcmp(comando, "ADD") == 0)
                fprintf(saida, "15");
            else if(strcmp(comando, "SUB") == 0)
                fprintf(saida, "16");
            else if(strcmp(comando, "MUL") == 0)
                fprintf(saida, "17");
            else if(strcmp(comando, "DIV") == 0)
                fprintf(saida, "18");
            else if(strcmp(comando, "REM") == 0)
                fprintf(saida, "19");
            
            else if(strcmp(comando, "JLE") == 0)
                fprintf(saida, "34");
            else if(strcmp(comando, "JDZ") == 0)
                fprintf(saida, "35");
            else if(strcmp(comando, "JGT") == 0)
                fprintf(saida, "36");
            else if(strcmp(comando, "JEQ") == 0)
                fprintf(saida, "37");
            else if(strcmp(comando, "JLT") == 0)
                fprintf(saida, "38");
            else if(strcmp(comando, "JGE") == 0)
                fprintf(saida, "39");
        }
        
        /* Lê a terceira palavra, que vai ser um número */
        fscanf(entrada, "%s", palavra);
        if (palavra[0] == ';') {
            while (fgetc(entrada) != '\n');
            continue;
        }
        
        numero = atoi(palavra);
        fprintf(saida, "%d ", numero);
        
    }
    
    
    fclose(entrada);
    fclose(saida);
    
    return 0;
}
