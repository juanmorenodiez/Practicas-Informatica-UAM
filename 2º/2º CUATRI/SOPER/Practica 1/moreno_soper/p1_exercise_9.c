/*
 * Ejemplo de codigo que genera un numero aleatorio y lo muestra por pantalla
 */
 #include <sys/types.h>
 #include <time.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/wait.h>

int main(int argc, char *argv[]) {
  int fd[2];
  int pid;
  int pipe_status;
  int num, num_leido1, num_leido2;

  /* Inicializa el generador con una semilla cualquiera, OJO! este metodo solo
   se llama una vez */
  srand(time(NULL));

  num = rand();

  pipe_status = pipe(fd);

  if (pipe_status == -1) {
    perror("Error creando la tubería 1\n");
    exit (EXIT_FAILURE);
  }

  pid = fork();
  if (pid < 0) {
    printf("Error al emplear fork\n");
    exit (EXIT_FAILURE);
  }

  if (pid == 0) {
    close(fd[0]);
    write(fd[1], &num, sizeof(int));
    printf("HIJO 1: número aleatorio %d\n", num);
    exit (EXIT_SUCCESS);
  }

  close(fd[1]);
  read(fd[0], &num, sizeof(int));
  printf ("El padre ha leido %d\n", num_leido1);
  waitpid(pid, NULL, 0);

  pipe_status = pipe(fd);

  if (pipe_status == -1) {
    perror("Error creando la tubería 2\n");
    exit (EXIT_FAILURE);
  }

  pid = fork();
  if (pid < 0) {
    printf("Error al emplear fork\n");
    exit (EXIT_FAILURE);
  }

  else if (pid == 0) {
    close(fd[1]);
    read (fd[0], &num_leido2, sizeof(int));
    printf("HIJO 2: el número aleatorio recibido es: %d\n", num_leido2);
    exit (EXIT_SUCCESS);
  }


  close(fd[0]);
  write(fd[1], &num_leido1, sizeof(int));
  waitpid(pid, NULL, 0);
  exit(EXIT_SUCCESS);




}
