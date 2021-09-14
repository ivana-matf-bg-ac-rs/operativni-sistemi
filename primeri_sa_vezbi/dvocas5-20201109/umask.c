#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* Program demonstrira koriscenje umask vrednosti
pri kreiranju fajlova. */

void error(char *message);

int main(int argc, char **argv){
    /* Postavlja se umask vrednost na 0. */
    umask(0);

    /* Kreira se fajl sa pravima pristupa rw-rw-rw-. */
    if (open("foo", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0)
        error("open()");

    /* Postavlja se umask vrednost na S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH. */
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    /* Kraira se fajl sa pravima pristupa rw-rw-rw-. */
    if (open("bar", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0)
        error("open()");

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);    
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
