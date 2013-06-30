#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define STRINGMAX 80

char charForHexInt (int n);             /* Retorna o caracter hexadecimal dado um número de 0 a 15 */
char *string4ForHexInt (int n);         /* Retorna uma string de 4 dígitos com o hexadecimal
                                         equivalente ao decimal n */
char *string4TwosCompForHexInt (int n); /* Retorna uma string de 4 dígitos com o hexadecimal
                                         equivalente ao complemento de 2 do decimal n */
char *string2ForHexInt (int n);         /* Retorna uma string de 2 dígitos com o hexadecimal
                                         equivalente ao decimal n */

int main (int argc, char *argv[]) {
    
    /*
     Declarações
     */
    
    FILE *entrada = NULL;               /* Arquivo de entrada */
    FILE *saida = NULL;                 /* Arquivo de saida */
    
    char *palavra = malloc(STRINGMAX * sizeof(char));   /* String para ler da entrada */
    char *comando = malloc(5 * sizeof(char));           /* String para escrever na saida */
        
    int linhaAnt = 0;                   /* Guarda o valor da linha anterior, para saber
                                            quantas linhas pular */
    int linha = 0;                      /* Guarda o valor da linha atual */
    int numero = 0;                     /* Guarda o valor de cada número lido da entrada */
    
    
    
    
    
    /*
     Abertura de arquivos
     */
    
    entrada = fopen(argv[1], "r");      /* Abre o arquivo de entrada */
    
    if(entrada == NULL ){               /* Encerra o programa caso o arquivo
                                            passado como argumento nao exista */
        printf("Nao foi possivel ler o arquivo de entrada\n");
        exit(-1);
    } 
    
    saida = fopen("saida.hip", "w");    /* Cria o arquivo de saída */
    
    
    
    
    
    /*
     Processamento do arquivo
     */
    
    while (!feof(entrada)) {        /* Enquanto não chegar no final do arquivo */
        
        char *num;
        
        fscanf(entrada, "%s", palavra);
        
        /* Pula comentários, se necessário */
        if (palavra[0] == ';') {
            while (fgetc(entrada) != '\n');
            continue;
        }
        
        linha = atoi(palavra);  /* A primeira palavra será o número da linha */
        
        /* Pula quantas linhas forem necessárias */
        while (linhaAnt++ < linha) fprintf(saida, "0000 ");
        
        
        
        fscanf(entrada, "%s", palavra);
        
        /* Pula comentários, se necessário */
        if (palavra[0] == ';') {
            while (fgetc(entrada) != '\n');
            continue;
        }
        
        /* A segunda palavra pode ser um número ou um comando */
        if (palavra[0] == '-' || palavra[0] == '+') {   /* Se for um número */
            numero = atoi(palavra);                     /* Transforma em inteiro */
            
            /* Se for negativo, pega o complemento de dois */
            if (numero < 0) num = string4TwosCompForHexInt(-numero);
            
            /* Se for positivo, basta transformar em hexadecimal */
            else num = string4ForHexInt(numero);
            
            fprintf(saida, "%s ", num);                 /* Escreve o número resultante na entrada */
            continue;                                   /* Não vai ter mais nada nessa linha;
                                                            começa de novo. */
        }
        
        
        else {                                          /* Se for um comando */
            comando = ++palavra;                        /* Pula o '{' */
            comando[3] = '\0';                          /* Sobrescreve o '}' com o fim da string */
            
            if(strcmp(comando, "LDA") == 0)             /* Compara o comando resultante com cada mnemônico */
                fprintf(saida, "0B");                   /* E imprime o hexadecimal correspondente */
            else if(strcmp(comando, "STA") == 0)
                fprintf(saida, "0C");
            else if(strcmp(comando, "INN") == 0)
                fprintf(saida, "1F");
            else if(strcmp(comando, "PRN") == 0)
                fprintf(saida, "29");
            else if(strcmp(comando, "STP") == 0) {      /* Se for STP não vai ter nada depois */
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
        
        fscanf(entrada, "%s", palavra);
        
        /* Pula comentários, se necessário */
        if (palavra[0] == ';') {
            while (fgetc(entrada) != '\n');
            continue;
        }
        
        /* Lê a terceira palavra, que vai ser um número */
        numero = atoi(palavra);             /* Transforma em int */
        num = string2ForHexInt(numero);     /* Transforma em hexadecimal */
        fprintf(saida, "%s ", num);         /* Imprime na saída */
        
    }
    
    
    fclose(entrada);                        /* Fecha ambos os arquivos e encerra o programa */
    fclose(saida);
    
    return 0;
}


/*
 Funções auxiliares
*/


char *string4ForHexInt (int n) {            /* Retorna uma string em hexadecimal */
    char *result = malloc(5*sizeof(char));  /* Alloca a string para retornar */
    
    int i;
    
    i = n % 16;                         /* i = primeiro dígito */
    n = (n - i)/16;                     /* Tira o primeiro digito de n */
    result[3] = charForHexInt(i);       /* coloca o primeiro digito em hex na string */
    i = n % 16;
    n = (n - i)/16;
    result[2] = charForHexInt(i);
    i = n % 16;
    n = (n - i)/16;
    result[1] = charForHexInt(i);
    result[0] = charForHexInt(n);       /* Repete para os outros 3 digitos */
    result[5] = '\0';                   /* Fim da string */
    
    return result;
}

char *string4TwosCompForHexInt (int n) {    /* Retorna uma string com o complemento de 2 de n */
    char *result = malloc(5*sizeof(char));
    char *binario = malloc(17*sizeof(char));
    
    int i, j;
    
    for (j = 0; j < 16; j++) {              /* Converte n para binário, com os bits já invertidos */
        i = n % 2;
        n = (n - i)/2;
        if (i == 0) binario[j] = '1';
        else binario[j] = '0';
    }
    
    for (j = 0; j < 16; j++) {              /* Soma 1 no número resultante */
        if (binario[j] == '1')
            binario[j] = '0';
        else if (binario[j] == '0') {
            binario[j] = '1';
            break;
        }
    }
    
    
    i = 1;
    n = 0;
    
    /* Transforma o binário em complemento de 2 em decimal */
    for (j = 0; j < 16; j++) {
        if (binario[j] == '1') n += i;
        i *= 2;
    }
    
    /* Transforma o decimal resultante numa string hexadecimal,
        com o mesmo algoritmo da string4ForHexInt() */
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
    
    free(binario);      /* Não vamos mais usar a string auxiliar 'binario' */
    
    return result;
}

char *string2ForHexInt (int n) {        /* Mesma ideia da string4ForHexInt,
                                            mas com apenas 2 dígitos */
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
    if (n >= 0 && n < 10)       /* Se for até 9, retorna o caracter do próprio número */
        return '0' + n;
    return 'A' + n - 10;        /* Se for de 10 a 15, retorna a letra maiúscula certa */
}
