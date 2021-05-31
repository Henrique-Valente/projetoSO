#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ    0
#define WRITE   1
#define BUFFER  256

int main() {
    int pipefd1[2], pipefd2[2];
    char message1[BUFFER] = "Teste";
    char message2[BUFFER] = "Teste2";
    char readmessage[BUFFER];
    pid_t pid;

    if (pipe(pipefd1) < 0 || pipe(pipefd2) < 0){
        perror("Pipe error!");
        exit(EXIT_FAILURE);
    }

    if((pid = fork()) < 0){
        perror("Fork error!");
        exit(EXIT_FAILURE);
    }

    else if(pid > 0){ //Parent process
        close(pipefd1[READ]);
        close(pipefd2[WRITE]);
        printf("PROCESSO PAI: ENVIEI: %s\n", message1);
        write(pipefd1[WRITE],message1, sizeof(message1));
        read(pipefd2[READ], readmessage, sizeof(readmessage));
        printf("PROCESSO PAI: RECEBI: %s\n", readmessage);
    }

    else{ //Child process
        close(pipefd1[WRITE]);
        close(pipefd2[READ]);
        read(pipefd1[READ],readmessage, sizeof(readmessage));
        printf("PROCESSO FILHO: RECEBI:%s\n", readmessage);
        printf("PROCESSO FILHO: ENVIEI:%s\n", message2);
        write(pipefd2[WRITE],message2, sizeof(message2));
    }
    
   
    return 0;
}