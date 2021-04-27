#include <stdio.h>
#define MAX_VALUE 100

void substring(int s, int f, char line[]){
    char word[MAX_VALUE];
    int max = f - s + 1;
    for(int i=0; i<=max; i++){
        word[i] = line[s];
        s = s+1;
    }
}

int main(){
    char test[MAX_VALUE] = "testando esta merda";
    printf("%s\n", word);
}