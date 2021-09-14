#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

/* Program blokira SIGQUIT signal, proverava da li je 
je taj signal pristigao u proces i odblokira ga. */

void error(char *message);

void on_sigquit(int signo);

int main(int argc, char **argv){
    sigset_t newmask, oldmask, pendmask; /* Promenljive za skupove signala. */

    /* Menja se ponasanje za SIGQUIT signal. */
    if (signal(SIGQUIT, on_sigquit) == SIG_ERR)
        error("signal()");

    /* Blokira se SIGQUIT signal. */
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        error("sigprocmask()");

    /* Proces salje samom sebi SIGQUIT signal. */
    kill(getpid(), SIGQUIT);
    kill(getpid(), SIGQUIT);
    kill(getpid(), SIGQUIT);

    /* Proverava se da li SIGQUIT signal ceka da pristigne u proces. */
    if (sigpending(&pendmask) < 0)
        error("sigpending()");
    if (sigismember(&pendmask, SIGQUIT))
        printf("SIGQUIT ceka da pristigne u proces.\n");

    /* Maska signala se postavlja na pocetnu vrednost. */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        error("sigprocmask()");

    printf("Odblokiran je SIGQUIT signal.\n");

    /* Generise se SIGQUIT signal. */
    kill(getpid(), SIGQUIT);

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}

void on_sigquit(int signo){
    /* Ispisuje se poruka. */
    printf("Uhvacen je SIGQUIT signal\n");

    /* Vraca se podrazumevano ponasanje za SIGALRM signal. */
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
        error("signal()");
}
