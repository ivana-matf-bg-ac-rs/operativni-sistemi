#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

/* Program ispisuje fajl status flegove za fajl koji je odredjen
deskriptorom koji je zadat u komandnoj liniji. */

void error(char *message);

int main(int argc, char **argv){
    int flags;      /* Statusni flegovi fajla. */
    int fd;         /* Fajl deskriptor. */

    assert(argc == 2);

    /* Otvara se fajl. Ako ne postoji, kreira se. Informacije o
    njemu se mogu ocitati pozivom "./a.out 3". */
    if (open("file.hole", O_WRONLY | O_TRUNC | O_APPEND) < 0)
        error("open()");    

    fd = atoi(argv[1]);

    /* Ocitavaju se fajl status flegovi. */
    if ((flags = fcntl(fd, F_GETFL, 0)) < 0)
        error("fcntl()");

    /* Ocitava se fleg za nacin pristupa fajlu. */
    switch(flags & O_ACCMODE){
        case O_RDONLY:
            printf("read only\n");
            break;
        case O_WRONLY:
            printf("write only\n");
            break;
        case O_RDWR:
            printf("read write\n");
            break;
        default:
            printf("unknown access mode\n");
    }

    /* Odredjuju se vrednosti ostalih flegova. */
    if (flags & O_APPEND)
        printf("append\n");
    if (flags & O_NONBLOCK)
        printf("non-block\n");

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
