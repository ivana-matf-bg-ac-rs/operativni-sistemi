#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>

/* Program demonstrira promenu tekuceg direktorjuma
procesa. */

void error(char *message);

int main(int argc, char **argv){
    char buffer[MAXPATHLEN];

    /* Menja se tekuci direktorijum pozivajuceg procesa. */
    if (chdir("/tmp") < 0)
        error("chdir()");

    /* Ocitava se tekuci direktorijum. */
    if (getcwd(buffer, MAXPATHLEN) == NULL)
        error("getcwd()");

    /* Ispisuje se tekuci direktorijum. */
    printf("Tekuci direktorijum je: %s\n", buffer);

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
