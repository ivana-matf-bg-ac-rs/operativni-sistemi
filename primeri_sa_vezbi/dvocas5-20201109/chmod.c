#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* Program ocitava prava pristupa fajla, demonstrira dodavanje odredjenog
prava pristupa, oduzimanje odredjenog prava pristupa i postavljanje
zadatog prava pristupa. */

void error(char *message);

int main(int argc, char **argv){
    struct stat stats;          /* Struktura za informacije o fajlu. */

    /* Ocitavaju se informacije o fajlu. */
    if (stat("bar", &stats) < 0)
        error("stat()");

    /* Izmenjuju se prava pristupa. */
    if (chmod("bar", (stats.st_mode & ~S_IWUSR) | S_IRGRP | S_IROTH) < 0)
        error("chmod()");

    /* Postavljanje prava pristupa. */
    if (chmod("foo", S_IRWXU) < 0)
        error("chmod()");

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
