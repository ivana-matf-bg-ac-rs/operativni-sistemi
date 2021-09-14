#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/* Program implementira funkcionalnosti system funkcije
iz standardne biblioteke.  */

void error(char *message);

void print_status(int status);

int system_our(const char* command); 

int main(int argc, char **argv){
    int status;             /* Status zavrsetka procesa. */

    /* Izvrsava se zadata komanda. */
    if ((status = system_our("date")) < 0)
        error("system()");

    /* Ispisuje se status zavrsetka. */
    print_status(status);


    /* Izvrsava se zadata komanda. */
    if ((status = system_our("nosuchcommand")) < 0)
        error("system()");

    /* Ispisuje se status zavrsetka. */
    print_status(status);

        /* Izvrsava se zadata komanda. */
    if ((status = system_our("who; exit 42")) < 0)
        error("system()");

    /* Ispisuje se status zavrsetka. */
    print_status(status);

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}

void print_status(int status){
    if (WIFEXITED(status))
        printf("Normalan zavrsetak, status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("Abnormalan zavrsetak, signal = %d\n", WTERMSIG(status));
    else if (WIFSTOPPED(status))
        printf("Abnormalan zavrsetak, signal = %d\n", WSTOPSIG(status));
}

int system_our(const char *command){
    pid_t pid;              /* Promenljiva za id procesa. */
    int status;             /* Promenljiva za status zavrsetka procesa. */

    /* Proverava se da li je zadata komanda. */
    if (command == NULL)
        return 1;

    /* Kreira se proces. */
    if ((pid = fork()) < 0)
        /* Ako je doslo do greske, vraca se -1. */
        return -1;

    else if (pid == 0){
        /* Child proces poziva shell da izvrsi komandu. */
        execl("/bin/sh", "sh", "-c", command, NULL);
        _exit(127);
    }

    /* Parent proces ceka da se child proces zavrsi i preuzima status zavrsetka. */
    for(;waitpid(pid, &status, 0) < 0;)
        if (errno != EINTR)
            return -1;

    /* Preuzeti status zavrsetka se vraca kao povratna vrednost. */
    return 0;
}
