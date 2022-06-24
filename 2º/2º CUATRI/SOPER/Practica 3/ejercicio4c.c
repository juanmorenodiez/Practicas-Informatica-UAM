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
  struct mq_attr attributes;

  attributes.mq_flags = 0;
  attributes.mq_maxmsg = 10;
  attributes.mq_curmsgs = 0;
  attributes.mq_msgsize = 2000;

  /*Abrimos las colas de las que vamos a leer*/
  mqd_t cola2 = mq_open(argv[1], O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR, &attributes);
  if (cola2 == (mqd_t)-1) {
    fprintf(stderr, "Error opening the queue1\n");
    return EXIT_FAILURE;
  }

  char msg[2000];

  if ((mq_receive(cola2, msg, 2000, NULL)) == -1) {
    fprintf(stderr, "Error sending message\n");
    return EXIT_FAILURE;
  }

  printf("%s", msg);

  mq_close(cola2);
  mq_unlink(argv[1]);

  return EXIT_SUCCESS;
}
