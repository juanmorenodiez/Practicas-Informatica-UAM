       pid_t wait(int *wstatus);
       pid_t waitpid(pid_t pid, int *wstatus, int options);
       int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
           waitpid(-1, &wstatus, 0);
       si_code     Set  to  one  of:  CLD_EXITED  (child   called   _exit(2));
                   stopped by signal); CLD_TRAPPED (traced child has trapped);
       through  the  use  of  the  prctl(2) PR_SET_CHILD_SUBREAPER operation);
       {
           pid_t cpid, w;
           int wstatus;
           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }
               printf("Child PID is %ld\n", (long) getpid());
               _exit(atoi(argv[1]));
               do {
                   w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
                   if (w == -1) {
                       perror("waitpid");
                       exit(EXIT_FAILURE);
                   }
                   if (WIFEXITED(wstatus)) {
                       printf("exited, status=%d\n", WEXITSTATUS(wstatus));
                   } else if (WIFSIGNALED(wstatus)) {
                       printf("killed by signal %d\n", WTERMSIG(wstatus));
                   } else if (WIFSTOPPED(wstatus)) {
                       printf("stopped by signal %d\n", WSTOPSIG(wstatus));
                   } else if (WIFCONTINUED(wstatus)) {
                       printf("continued\n");
                   }
               } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
               exit(EXIT_SUCCESS);
           }
       }
