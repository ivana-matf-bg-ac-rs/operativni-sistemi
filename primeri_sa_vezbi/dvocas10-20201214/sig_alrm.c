#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* Program menja ponasanje za SIGALRM signal u main funkciji
i u signal hendleru. */

void error(char *message);

void on_sigalrm(int signo);

int main(int argc, char **argv){
    /* Menja se ponasanje za SIGALRM signal. */
    if (signal(SIGALRM, on_sigalrm) == SIG_ERR)
        error("signal()");

    /* Postavlja se alarm za 5 sekundi. */
    alarm(5);

    /* Pauzira se program do pristizanja alarma. */
    while(1)
        pause();
    
    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}

void on_sigalrm(int signo){
    /* Ispisuje se poruka. */
    printf("Uhvacen je SIGALRM signal\n");

    /* Vraca se podrazumevano ponasanje za SIGALRM signal. */
    if (signal(SIGALRM, SIG_DFL) == SIG_ERR)
        error("signal()");

    /* Ponovo se postavlja alarm za 5 sekundi. */
    alarm(5);
}
