#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define N_READ 1
#define SECS 0
#define SEM1 "/lectura1"
#define SEM2 "/escritura1"

int lectores = 0;
int flag1 = 1;
int flag2 = 1;

void manejador_SIGINT(int sig) {
    printf("Padre mandando señales a hijos %d\n", getpid());
    fflush(stdout);
    flag2 = -1;
    kill (0, SIGTERM);
}

void manejador_SIGTERM(int sig) {
    printf("Hijo ha recibido señal (PID %d)\n", getpid());
    fflush(stdout);
    flag1 = -1;
}

void Leer () {
  printf ("R-INI <%d>\n", getpid());
  fflush (stdout);
  sleep(1);
  printf ("R-FIN <%d>\n", getpid());
  fflush (stdout);
}

void Escribir () {
  printf ("W-INI <%d>\n", getpid());
  fflush (stdout);
  sleep(1);
  printf ("W-FIN <%d>\n", getpid());
  fflush (stdout);
}

void Lectura(sem_t *sem_lectura, sem_t *sem_escritura) {
  sem_wait(sem_lectura);
  lectores++;

  if (lectores == 1)
    sem_wait(sem_escritura);
  sem_post(sem_lectura);

  Leer();

  sem_wait(sem_lectura);
  lectores--;
  if (lectores == 0)
    sem_post(sem_escritura);
  sem_post(sem_lectura);
}

void Escritura(sem_t *sem_escritura) {
  sem_wait(sem_escritura);

  Escribir();

  sem_post(sem_escritura);
}

int main (void) {
  pid_t pid;
  sem_t *sem_lectura = NULL, *sem_escritura = NULL;
  sigset_t set, oset;
  sigset_t set1, oset1;
  int i;

  if ((sem_lectura = sem_open(SEM1, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
    perror("sem_open_lectura");
    exit(EXIT_FAILURE);
  }

  if ((sem_escritura = sem_open(SEM2, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
    perror("sem_open_escritura");
    exit(EXIT_FAILURE);
  }

  sem_unlink(SEM1);
  sem_unlink(SEM2);

  struct sigaction act;
  sigemptyset(&(act.sa_mask));
  act.sa_flags = 0;

  act.sa_handler = manejador_SIGINT;
  if (sigaction(SIGINT, &act, NULL) < 0) {
    perror("sigaction");
    exit(EXIT_FAILURE);
  }

  act.sa_handler = manejador_SIGTERM;
  if (sigaction(SIGTERM, &act, NULL) < 0) {
    perror("sigaction");
    exit(EXIT_FAILURE);
  }

  sigemptyset(&set);
  sigaddset(&set, SIGINT);

  for (i=0; i < N_READ; i++) {
    pid = fork();

    if(pid <  0){
			printf("Error al emplear fork\n");
			exit(EXIT_FAILURE);
		}

    else if (pid == 0) {
      if (sigprocmask(SIG_BLOCK, &set, &oset) < 0) {
        perror("sigprogmask");
        exit(EXIT_SUCCESS);
      }

      while(flag1 > 1) {
        Lectura(sem_lectura, sem_escritura);
        sleep(SECS);
      }
      exit(EXIT_SUCCESS);
    }
  }

  printf("PID del padre: %d\n", getpid());

  sigemptyset(&set1);
  sigaddset(&set1, SIGTERM);

  if (sigprocmask(SIG_BLOCK, &set1, &oset1) < 0) {  /*Bloqueo señal sigterm*/
    perror("sigprocmask");
    exit(EXIT_FAILURE);
  }

  while (flag2>0) {
    Escritura(sem_escritura);
    sleep(SECS);
  }

  while (wait(NULL) > 0);
  exit(EXIT_SUCCESS);
}
