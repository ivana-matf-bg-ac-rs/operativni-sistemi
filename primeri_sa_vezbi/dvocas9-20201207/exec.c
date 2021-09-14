#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/* Program demonstrira pozivanje nekoliko exec funkcija. */

void error(char *message);

void print_status(int status);

int main(int argc, char **argv){
    pid_t pid;              /* Promenljiva za id procesa. */
    int status;             /* Promenljiva za status zavrsetka. */

    /* Kreira se proces. */
    if ((pid = fork()) < 0)
        error("fork()");
    else if (pid == 0){
        /* Child proces izvrsava program args. */
        execlp("args", "args", "prvi", "drugi", NULL);
        error("execlp()");
    }

    /* Parent proces ceka da se zavrsi child proces i da preuzme
    njegov status zavrsetka. */
    if (wait(&status) != pid)
        error("wait()");

    /* Ispisuje se informacija o nacinu i statusu zavrsetka. */
    print_status(status);

    /* Kreira se proces. */
    if ((pid = fork()) < 0)
        error("fork()");
    else if (pid == 0){
        /* Child proces izvrsava program args. */
        execl("args", "args", "prvi", "drugi", NULL);
        error("execl()");
    }

    /* Parent proces ceka da se zavrsi child proces i da preuzme
    njegov status zavrsetka. */
    if (wait(&status) != pid)
        error("wait()");

    /* Ispisuje se informacija o nacinu i statusu zavrsetka. */
    print_status(status);

    /* Kreira se proces. */
    if ((pid = fork()) < 0)
        error("fork()");
    else if (pid == 0){
        /* Child proces izvrsava program ls. */
        execlp("ls", "ls", NULL);
        error("execlp()");
    }

    /* Parent proces ceka da se zavrsi child proces i da preuzme
    njegov status zavrsetka. */
    if (wait(&status) != pid)
        error("wait()");

    /* Ispisuje se informacija o nacinu i statusu zavrsetka. */
    print_status(status);

    /* Kreira se proces. */
    if ((pid = fork()) < 0)
        error("fork()");
    else if (pid == 0){
        /* Child proces izvrsava program ls. */
        execl("ls", "ls", NULL);
        error("execl()");
    }

    /* Parent proces ceka da se zavrsi child proces i da preuzme
    njegov status zavrsetka. */
    if (wait(&status) != pid)
        error("wait()");

    /* Ispisuje se informacija o nacinu i statusu zavrsetka. */
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
