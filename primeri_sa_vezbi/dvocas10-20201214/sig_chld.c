#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
 #include <unistd.h>

/* Program demonstira rad sa SIGCHLD signalom. */

void error(char *message);

void on_sigchld(int signo);

int main(int argc, char **argv){
    int i;              /* Brojac. */
    pid_t pid;          /* Promenljiva za id procesa. */

    /* Menja se ponasanje za SIGCHLD signal. */
    if (signal(SIGCHLD, on_sigchld) == SIG_ERR)
        error("signal()");

    /* Pravi se 5 procesa. */
    for (i=0 ; i<5; i++){
        if ((pid = fork()) < 0)
            error("fork()");
        else if (pid == 0){
            /* Child proces ispisuje poruku. */
            printf("Pozdrav iz child procesa broj %d\n", i);

            /* Proces se uspavljuje na i sekundi. */
            sleep(i);

            /* Zavrsava se child proces. */
            exit(EXIT_SUCCESS);
        }

        /* Parent proces nastavlja sa petljom. */
    }

    /* Parent proces nastavlja sa radom. */
    while(1)
        pause();

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}

void on_sigchld(int signo){
    int status;             /* Promenljiva za status zavrsetka. */
    pid_t pid;              /* Promenljiva za id procesa. */

    /* Ispisuje se poruka. */
    printf("Uhvacen je SIGCHLD signal.\n");

    /* Ocitava se status zavrsetka zavrsenog procesa. */
    for(;(pid = waitpid(-1, &status, WNOHANG)) > 0;)
        printf("Preuzet je status zavrsetka: %d\n", status);

    /* Obradjuje se ukoliko je nastala greska. */
    if (pid < 0 && errno != ECHILD)
        error("waitpid()");
}
