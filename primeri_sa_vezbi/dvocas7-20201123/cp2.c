#include <stdio.h>
#include <stdlib.h>

/* Program kopira podatke sa standardnog ulaza na standardni izlaz
pomocu funkcija standardne I/O biblioteke. */

#define BUFFER_SIZE 20

void error(char *message);

int main(int argc, char **argv){
    char buffer[BUFFER_SIZE];           /* Bafer za razmenu poruka. */

    /* U petlji se sa standardnog ulaza ucitavaju podaci... */
    for (;fgets(buffer, BUFFER_SIZE, stdin) != NULL;){
        /* ... i ispisuju na standardni izlaz. */
        if (fputs(buffer, stdout) == EOF)
            error("fputs()");
    }

    /* Ako je bilo greske, obradjuje se. */
    if (ferror(stdin))
        error("fgets()");

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
