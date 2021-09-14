#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/* Program demonstrira pravljenje rupe u fajlu, tzv. "hole". */

void error(char *message);

int main(int argc, char **argv){
    char buffer1[] = "qwertyuiop";  /* Bafer za prvi sadrzaj koji se upisuje u fajl. */
    char buffer2[] = "QWERTYUIOP";  /* Bafer za drugi sadrzaj koji se upisuje u fajl. */
    int fd;                         /* Fajl deskriptor. */

    /* Otvara se fajl. Ako ne postoji, kreira se. */
    if ((fd = open("file.hole", O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH)) < 0)
        error("open()");

    /* Upisuje se u fajl sadrzaj prvog bafera. */
    if (write(fd, buffer1, 10) != 10)
        error("write()");

    /* Pomera se ofset za 1000 bajtova. */
    if (lseek(fd, 1000, SEEK_CUR) < 0)
        error("lseek()");

    /* Upisuje se u fajl sadrzaj drugog bafera. */
    if (write(fd, buffer2, 10) != 10)
        error("write()");

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}