#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/* Program demonstrira kreiranje procesa i koriscenje promenljivih. */

int x = 1;                      /* Globalna promenljiva. */          

void error(char *message);

int main(int argc, char **argv){
    int y = 10;                 /* Lokalna promenljiva. */
    pid_t pid;                  /* Promenljiva za identifikator procesa. */
    char buffer[] = "Hello\n";  /* Promenljiva za poruku. */

    /* Ispisuje se poruka na izlaz pomocu sistemskog poziva write. */
    if (write(STDOUT_FILENO, buffer, sizeof(buffer) - 1) != sizeof(buffer) - 1)
        error("write()");

    /* Ispisuje se druga poruka pomocu funkcije standardne biblioteke. */
    fprintf(stdout, "world\n");

    /* Kreira se proces. */
    if ((pid = fork()) < 0)
        error("fork()");
    else if (pid == 0){
        /* Child proces. */
        x++;
        y++;
    } else {
        sleep(2);
    }

    /* Oba procesa ispisuju poruku. */
    printf("pid = %d, ppid = %d, x = %d, y = %d\n", getpid(), getppid(), x, y);

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
