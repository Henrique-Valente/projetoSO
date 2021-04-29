#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main(int argc, char *argv[]){
    char* fileName = argv[2];
    int cur_line = 0;  //Guarda o numero da linha atual
    FILE* file = fopen(fileName, "r"); //Abrir o ficheiro recebido
    char line[256]; //Guarda uma linha
    char* needle = strdup(argv[1]); //Palavra que queremos encontrar
    char* haystack; //Irá representar cada linha
    char* ptr; 
    
    
    while (fgets(line, sizeof(line), file)) { //Guarda cada linha numa string
        list *columns = list_new(); //Guarda o numero de colunas
        cur_line++; //Incrementa o numero da linha atual
        haystack = strdup(line);
        ptr = haystack;
        while( (ptr = strstr(ptr, needle)) != NULL){
            int pos = strlen(haystack) - strlen(ptr) + 1;
            list_add_last(pos,columns);
            ptr++;
        }

        if(list_size(columns) != 0){   //Faz o print dos valores
            printf("[%d:", cur_line);
            while(list_size(columns) != 1){
                printf("%d,", list_get_first(columns));
                list_remove_first(columns);
            }
            printf("%d", list_get_first(columns));
            list_remove_first(columns);
            printf("]\n");
        }

        free(columns);
    }

    fclose(file);
    return 0;
}