#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUFFER_SIZE 10

/* Program demonstrira citanje iz jednog kraja pajpa i 
sa standardnog ulaza. */

void error(char *message);

int main(int argc, char **argv){
    int filedes[2];         /* Fajl deskriptori koji se odnose na krajeve pajpa. */
    pid_t pid;              /* Proces id child-a. */
    char buffer[BUFFER_SIZE];   /* Bafer za razmenu poruka. */
    int count;              /* Velicina poruke koja se ucitava odnosno salje. */

    /* Kreira se pajp. */
    if (pipe(filedes) < 0)
        error("pipe()");

    /* Kreira se proces. */
    if ((pid = fork()) < 0)
        error("fork()");
    else if (pid == 0){
        /* Child proces zatvara fajl deskriptore koji mu ne trebaju. */
        if (close(filedes[0]) < 0)
            error("close()");

        /* Uspavljuje se na 10 sekundi. */
        sleep(10);

        /* Salje poruku parent procesu. */
        strcpy(buffer, "Pozdrav\n");
        if (write(filedes[1], buffer, strlen(buffer)) != strlen(buffer))
            error("write()");

        /* Zavrsava se child proces. */
        exit(EXIT_SUCCESS);
    }

    /* Parent proces zatvara fajl deskriptore koji mu ne trebaju. */
    if (close(filedes[1]) < 0)
        error("close()");

    /* Ucitava podatke iz pajpa. */
    while((count = read(filedes[0], buffer, BUFFER_SIZE)) > 0)
        if (write(STDOUT_FILENO, buffer, count) != count)
            error("write()");

    if (count < 0)
        error("read()");

    /* Ucitava podatke sa standardnog ulaza. */
    while((count = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
        if (write(STDOUT_FILENO, buffer, count) != count)
            error("write()");

    if (count < 0)
        error("read()");

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
