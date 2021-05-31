#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>

void printArray(int array[], int n){
    for(int i=0;i<n;i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void printMatrix(int n, int matrix[][n]){
    for(int i=0;i<n;i++){
        for(int j=0; j<n;j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) { 
  pid_t pid;

  if(argc < 4){
        printf("Not enough arguments!\n");
        exit(EXIT_FAILURE);
  } 

  int m = atoi(argv[2]); //Numero de processos
  int k = atoi(argv[3]); //Threshold
  FILE* f = fopen(argv[1],"r");
  size_t str_size = 0;
  char*  str = NULL;
  getline(&str, &str_size, f);
  int n = atoi(str);
  int matrix[n][n];
  int count = 0;
  int i=0;
  int j=0;
  
  /*REVER ESTE PEDAÇO DE CÓDIGO E TENTAR FAZER DE OUTRA FORMA*/
  while(getline(&str, &str_size, f) > 0){ //Passar a matriz do TXT para código
      char* tokens = strtok(str," "); // Partir str em tokens
      while( tokens != NULL ) {
        matrix[i][j]=atoi(tokens);
        tokens=strtok(NULL," ");
        j++;
      }
      i++;
      j=0;
  }
  
  /*Inicializar a memória partilhada pelos processos filhos*/

  int *sharedMem = mmap(NULL, m*sizeof(int), PROT_READ|PROT_WRITE,
		       MAP_SHARED|MAP_ANONYMOUS, 0, 0);
  
  if(sharedMem == MAP_FAILED){
    perror("mmap");
    exit(EXIT_FAILURE);
  }

  for(i = 0; i < m; i++)
    sharedMem[i] = 0;

  
  for(i=0; i<m; i++){
      if((pid = fork()) < 0){
          printf("Couldn't fork parent!");
          exit(EXIT_FAILURE);
      }
      else if(pid == 0){
        for(j = 0; j < n; j++)
            if(j % m == i) 
            for(int q = 0; q < n; q++) 
                if(matrix[j][q] > k)
	                sharedMem[i]++;
        exit(EXIT_SUCCESS);
      }
  }

  for(i = 0; i < m; i++)  {   
    if ( waitpid(-1, NULL, 0) < 0) {
      printf("Couldn't wait for child to finish!");
      exit(EXIT_FAILURE);
    }
  } 

  for(i = 0; i<m ; i++){
      count += sharedMem[i];
  }
  printf("%d\n",count);
  
  if (munmap(sharedMem, sizeof(sharedMem)) < 0) {
    perror("Couldn't free mmap memory!");
    exit(EXIT_FAILURE);
  }
 
  fclose(f);
  exit(EXIT_SUCCESS);
}