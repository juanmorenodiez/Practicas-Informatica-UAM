#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

/* manejador_SIGALRM:*/
void manejador_SIGTERM(int sig){
  printf("Soy %d y he recibido la señal SIGTERM\n", getpid());
  fflush(stdout);
}

#define N_ITER 5
int main (void) {
  pid_t pid;
  int counter;
  struct sigaction act;
  sigset_t set, oset;

  act.sa_handler = manejador_SIGTERM;
  sigemptyset(&(act.sa_mask));
  act.sa_flags = 0;

  if (sigaction(SIGTERM, &act, NULL) < 0) {
      perror("sigaction");
      exit(EXIT_FAILURE);
  }

  pid = fork();
  if (pid < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid == 0) {
    sigaddset(&set, SIGTERM);
    sigprocmask(SIG_SETMASK, &set, &oset);
    while(1) {
      for (counter = 0; counter < N_ITER; counter++) {
        printf("%d\n", counter);
        sleep(1);
      }
      sigsuspend(&oset);
      exit(EXIT_SUCCESS);
    }
  }
  sleep(10);

  if (kill(pid, SIGTERM) < 0){
      perror("SIGTERM");
      exit(EXIT_FAILURE);
  }
  waitpid(pid, NULL, 0);
  exit(EXIT_SUCCESS);
}
