#include <stdio.h>
#include <stdlib.h>

/* Program ispisuje argumente komandne linije na izlaz. */

void error(char *message);

int main(int argc, char **argv){
    int i;              /* Promenljiva koja ce sluziti kao brojac u petlji. */

    /* Ispisuju se argumenti komandne linije. */
    for (i=0; i<argc; i++)
        printf("argv[%d] = %s\n", i, argv[i]);

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
