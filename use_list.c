#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(){
    list *l1 = list_new();
    int i = 0;
    

    list_add_first(10,l1);
    list_add_first(11,l1);
    list_add_first(12,l1);
    list_add_first(13,l1);
    i = list_get_last(l1);
    list_print(l1);
    printf("Último valor: %d\n", i);

    printf("Último valor removido: ");
    list_remove_last(l1);
    list_print(l1);
}