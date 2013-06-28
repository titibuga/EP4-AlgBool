#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define STRINGMAX 80

char charForHexInt (int n);
char *string4ForHexInt (int n);
char *string4TwosCompForHexInt (int n);
char *string2ForHexInt (int n);

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
        
        char *num;
        
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
            if (numero < 0) num = string4TwosCompForHexInt(-numero);
            else num = string4ForHexInt(numero);
            fprintf(saida, "%s ", num);
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
        num = string2ForHexInt(numero);
        fprintf(saida, "%s ", num);
        
    }
    
    
    fclose(entrada);
    fclose(saida);
    
    return 0;
}

char *string4TwosCompForHexInt (int n) {
    char *result = malloc(5*sizeof(char));
    char *binario = malloc(17*sizeof(char));
    
    int i, j;
    
    printf("%d\n", n);
    
    for (j = 0; j < 16; j++) {
        i = n % 2;
        n = (n - i)/2;
        if (i == 0) binario[j] = '1';
        else binario[j] = '0';
    }
    
    printf("%s\n", binario);
    
    for (j = 0; j < 16; j++) {
        if (binario[j] == '1')
            binario[j] = '0';
        else if (binario[j] == '0') {
            binario[j] = '1';
            break;
        }
    }
    
    printf("%s\n", binario);

    i = 1;
    n = 0;
    for (j = 0; j < 16; j++) {
        if (binario[j] == '1') n += i;
        i *= 2;
    }
    printf("%d\n", n);

    
    i = n % 16;
    n = (n - i)/16;
    result[3] = charForHexInt(i);
    i = n % 16;
    n = (n - i)/16;
    result[2] = charForHexInt(i);
    i = n % 16;
    n = (n - i)/16;
    result[1] = charForHexInt(i);
    result[0] = charForHexInt(n);
    result[5] = '\0';
    
    printf("%s\n", result);
    
    free(binario);
    
    return result;
}

char *string4ForHexInt (int n) {
    char *result = malloc(5*sizeof(char));
    
    int i;
    
    i = n % 16;
    n = (n - i)/16;
    result[3] = charForHexInt(i);
    i = n % 16;
    n = (n - i)/16;
    result[2] = charForHexInt(i);
    i = n % 16;
    n = (n - i)/16;
    result[1] = charForHexInt(i);
    result[0] = charForHexInt(n);
    result[5] = '\0';
    
    printf("%s\n", result);
    
    return result;
}

char *string2ForHexInt (int n) {
    char *result = malloc(2*sizeof(char));
        
    int i = 0;
    i = n % 16;
    n = (n - i)/16;
    result[1] = charForHexInt(i);
    result[0] = charForHexInt(n);
    result[2] = '\0';
        
    return result;
}

char charForHexInt (int n) {
    if (n >= 0 && n < 10)
        return '0' + n;
    return 'A' + n - 10;
}
