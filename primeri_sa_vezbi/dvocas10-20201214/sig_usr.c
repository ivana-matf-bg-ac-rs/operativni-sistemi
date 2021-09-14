#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* Program menja ponasanje za SIGUSR1 i SIGUSR2 signale. */

void error(char *message);

void on_sigusr(int signo);

int main(int argc, char **argv){
    /* Menja se ponasanje za SIGUSR1 i SIGUSR2 signale. */
    if (signal(SIGUSR1, on_sigusr) == SIG_ERR)
        error("signal()");

    if (signal(SIGUSR2, on_sigusr) == SIG_ERR)
        error("signal()");

    /* Pauzira se proces. */
    while(1)
        pause();

    /* Zavrsava se proces. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}

void on_sigusr(int signo){
    if (signo == SIGUSR1)
        printf("Uhvacen je SIGUSR1 signal\n");
    else if (signo == SIGUSR2)
        printf("Uhvacen je SIGUSR2 signal\n");
    else 
        printf("Uhvacen je nepoznati signal\n");
}
