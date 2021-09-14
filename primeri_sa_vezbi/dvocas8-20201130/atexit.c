#include <stdio.h>
#include <stdlib.h>

/* Program poziva funkcije koje treba da se izvrse prilikom
pozivanja exit funkcije. */

void handler1(void);

void handler2(void);

void error(char *message);

int main(int argc, char **argv){
    /* Registruju se funkcije koje treba da se izvrse
    prilikom zavrsetka programa. */
    if (atexit(handler1) != 0)
        error("atexit()");
    if (atexit(handler1) != 0)
        error("atexit()");
    if(atexit(handler2) != 0)
        error("atexit()");

    /* Ispisuje se poruka iz main funkcije */
    printf("Hello from main function!!!\n");

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void handler1(void){
    printf("Hello from handler1!!!\n");
}

void handler2(void){
    printf("Hello from handler2!!!\n");
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
