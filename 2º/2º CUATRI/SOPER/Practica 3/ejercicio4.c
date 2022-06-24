

#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char *argv[]) {
  if (argc != 4){
    printf("Parámetros incorrectos. La estructura tiene que ser:\n./ejercicio4 nombre_fichero nombre_cola1 nombre_cola2");
    exit(EXIT_FAILURE);
  }

  pid_t pid;
  pid_t pid1;
  pid_t pid2;

  struct mq_attr attributes;

  attributes.mq_flags = 0;
  attributes.mq_maxmsg = 10;
  attributes.mq_curmsgs = 0;
  attributes.mq_msgsize = 2000;

  mqd_t cola1 = mq_open(argv[2], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attributes);
  if (cola1 == (mqd_t)-1) {
    fprintf(stderr, "Error opening the queue\n");
    return EXIT_FAILURE;
  }

  mqd_t cola2 = mq_open(argv[3], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attributes);
  if (cola2 == (mqd_t)-1) {
    fprintf(stderr, "Error opening the queue\n");
    return EXIT_FAILURE;
  }

  pid = fork();
  if (pid < 0) {
    printf("Error al emplear fork\n");
    exit(EXIT_FAILURE);
  }

  else if (pid == 0) {
    execl("./ejercicio4a","./ejercicio4a", argv[1], argv[2], NULL);
    exit(EXIT_SUCCESS);
  }

  else if (pid > 0) {
    wait(&pid);
    pid1 = fork();

    if (pid1 < 0) {
      printf("Error al emplear fork\n");
      exit(EXIT_FAILURE);
    }

    else if (pid1 == 0) {
      execl("./ejercicio4b","./ejercicio4b", argv[2], argv[3], NULL);
      exit(EXIT_SUCCESS);
    }

    else if (pid1 > 0) {
      wait(&pid1);
      pid2 = fork();

      if (pid2 < 0) {
        printf("Error al emplear fork\n");
        exit(EXIT_FAILURE);
      }

      else if (pid2 == 0) {
        execl("./ejercicio4c","./ejercicio4c", argv[3], NULL);
        exit(EXIT_SUCCESS);
      }

      else if (pid2 > 0) {
        wait(&pid2);
        mq_close(cola1);
        mq_close(cola2);
        mq_unlink(argv[2]);
        mq_unlink(argv[3]);
        return EXIT_SUCCESS;
      }
    }
  }


}
