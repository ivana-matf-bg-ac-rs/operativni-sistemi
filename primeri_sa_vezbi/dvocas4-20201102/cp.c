#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* Program kopira ulaz na izlaz uz pomoc sistemskih poziva
read i write. */

#define BUFFER_SIZE 4096

void error(char *message);

int main(int argc, char **argv){
    int n;          /* Broj ucitanih odnosno poslatih bajtova. */
    char buffer[BUFFER_SIZE];   /* Bafer za razmenu poruka. */

    /* Ucitava se sadrzaj sa standardnog ulaza i pise se na
    standardni izlaz. */
    for (;(n = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0;)
        if (write(STDOUT_FILENO, buffer, n) != n)
            error("write()");

    /* Obradjuje se greska ukoliko je nastala u read
    sistemskom pozivu. */
    if (n < 0)
        error("read()");

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}