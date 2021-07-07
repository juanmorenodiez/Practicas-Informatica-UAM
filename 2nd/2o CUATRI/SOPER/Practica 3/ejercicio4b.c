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

  /*Abrimos las colas de las que vamos a leer y escribir*/
  mqd_t cola1 = mq_open(argv[1],O_RDONLY, S_IRUSR | S_IWUSR, &attributes);
  if (cola1 == (mqd_t)-1) {
    fprintf(stderr, "Error opening the queue1\n");
    return EXIT_FAILURE;
  }


  mqd_t cola2 = mq_open(argv[2], O_WRONLY, S_IRUSR | S_IWUSR, &attributes);
  if (cola2 == (mqd_t)-1) {
    mq_unlink(argv[1]);
    mq_close(cola1);
    fprintf(stderr, "Error opening the queue2\n");
    return EXIT_FAILURE;
  }

  int i = 0;
  char msg[2000];

  if ((mq_receive(cola1, msg, 2000, NULL)) == -1) {
    fprintf(stderr, "Error sending message\n");
    return EXIT_FAILURE;
  }

  while (i  < strlen(msg)){
      if (msg[i] == 123)
        msg[i] = 97;
      else
        msg[i] +=1;
      i++;
}

  if(mq_send(cola2, msg, sizeof(msg), 1) == -1) {
      perror("Error sending message");
      exit(EXIT_FAILURE);
  }

  else {
      printf("Message converted sent: %s", msg);
  }

}
