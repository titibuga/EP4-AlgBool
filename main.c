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
    char *comando = malloc(3 * sizeof(char));
    
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
        fscanf(entrada, "%s", palavra);
        if (palavra[0] == ';') {
            while (fgetc(entrada) != '\n');
            continue;
        }
        
        if (palavra[0] == '-' || palavra[0] == '+') {
            numero = atoi(palavra);
            fprintf(saida, "%d ", numero);
            continue;
        }
        else {
            comando = ++palavra;
            comando[3] = '\0';
            
            fprintf(saida, "%s ", comando);
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
