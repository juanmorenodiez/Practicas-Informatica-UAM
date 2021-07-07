#include <mqueue.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
  char aviso[80];
} Mensaje;


int main (int argc, char *argv[]) {
  struct mq_attr attributes;

  attributes.mq_flags = 0;
  attributes.mq_maxmsg = 10;
  attributes.mq_curmsgs = 0;
  attributes.mq_msgsize = 2000;

  /* abrimos la cola que pasamos como segundo argumento*/
  mqd_t cola1 = mq_open(argv[2], O_RDWR, S_IRUSR | S_IWUSR, &attributes);
  if (cola1 == (mqd_t)-1) {
    fprintf(stderr, "Error opening the queue\n");
    return EXIT_FAILURE;
  }

  int fd_shm = open(argv[1], O_RDONLY);

  if (fd_shm == -1) {
    fprintf(stderr, "Error opening the shared memory segment for the file\n");
    return EXIT_FAILURE;
  }

  char *message = (char*)mmap(0, 2000 , PROT_READ, MAP_SHARED, fd_shm, 0);

  Mensaje msg;
  strcpy(msg.aviso, message);

  if (mq_send(cola1, message , 2000 , 1) == -1) {
    fprintf (stderr, "Error sending message\n");
  }

  else {
    printf("Message sent: %s\n", message);
  }


  return EXIT_SUCCESS;

}
