#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* Program demonstrira citanje sa standardnog ulaza
na standardni izlaz uz preusmeravanje fajl deskriptora
na odgovarajuce fajlove. */

#define BUFFER_SIZE 256

void error(char *message);

int main(int argc, char **argv){
    int file, copy;             /* Fajl deskriptori. */
    char buffer[BUFFER_SIZE];   /* Bafer za razmenu poruka. */
    int n;                      /* Broj procitanih odnosno poslatih bajtova. */

    /* Proverava se da postoje 3 argumenta komandne linije. */
    assert(argc == 3);

    /* Otvara se fajl za citanje. */
    if ((file = open(argv[1], O_RDONLY)) < 0)
        error("open()");

    /* Otvara se fajl za pisanje. */
    if ((copy = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH)) < 0)
        error("open()");

    /* Preusmerava se standardni ulaz. */
    if (dup2(file, STDIN_FILENO) < 0)  
        error("dup2()");

    /* Preusmerava se standardni izlaz. */
    if (dup2(copy, STDOUT_FILENO) < 0)
        error("dup2()");

    /* Cita se sa standardnog ulaza i pise se na standardni izlaz. */
    while((n = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
        if (write(STDOUT_FILENO, buffer, n) != n)
            error("write()");

    /* Ukoliko je nastala greska u sistemskom pozivu read,
    obradjuje se. */
    if (n < 0)
        error("read()");

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}