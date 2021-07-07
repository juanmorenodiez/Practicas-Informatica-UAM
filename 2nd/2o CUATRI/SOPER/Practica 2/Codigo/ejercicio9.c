#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N_PROC 4

int main(void){
  pid_t pid, participante;
  FILE *pf;

  pid = fork();

  if (pid < 0) {
    printf("Error al emplear fork\n");
    exit(EXIT_FAILURE);
  }

  else if (pid == 0) {
    for (i=0 ; i < N_PROC; i++) {
      participante = fork();

      if (participante < 0) {
        printf("Error al emplear fork\n");
        exit(EXIT_FAILURE);
      }

      if (participante == 0) {
        pf = fopen("fichero.txt", "w");
        if (f == NULL) {
          return -1;
        }
        fprintf("Mi PID es: %d", getpid());
        usleep(3);
      }

      if (participante > 0) {

      }
    }
  }






}
