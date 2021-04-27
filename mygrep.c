#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VALUE 10

int main(int argc, char *argv[]){
    char* fileName = argv[2];
    int cur_line = 0;  //Guarda o numero da linha atual
    FILE* file = fopen(fileName, "r"); //Abrir o ficheiro recebido
    char line[256]; //Guarda uma linha
    char* needle = strdup(argv[1]); //Palavra que queremos encontrar
    char* haystack; //Irá representar cada linha
    char* ptr; 
    int i = 0;
    

    while (fgets(line, sizeof(line), file)) { //Guarda cada linha numa string
        int* columns = malloc(sizeof(int) * MAX_VALUE); //Guarda o numero de colunas
        for(int j=0;j<MAX_VALUE;j++) columns[j] = -1;  //Coloca o valor das posicoes do array a -1
        cur_line++; //Incrementa o numero da linha atual
        haystack = strdup(line);
        ptr = haystack;
        while( (ptr = strstr(ptr, needle)) != NULL){
            int pos = strlen(haystack) - strlen(ptr) + 1;
            columns[i] = pos;
            ptr++;
            i++;
        }
        i = 0; // Reset do i
        if(columns[i] != -1){   //Faz o print dos valores
            printf("[%d:", cur_line);
            while(columns[i+1] != -1){
                printf("%d,", columns[i]);
                i++;
            }
            printf("%d", columns[i]);
            printf("]\n");
        }
        i = 0; // Reset novamente
        
        free(columns);
    }

    fclose(file);
    return 0;
}