#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

/* Program kopira fajl metodom memorijskog mapiranja. */

void error(char *message);

int main(int argc, char **argv){
    int file, copy;         /* Deskriptori fajla koji se kopira i kopije. */
    char *src, *dst;        /* Adrese pocetaka memorijski mapiranih regiona. */
    struct stat stats;      /* Struktura sa informacijama o fajlu. */

    /* Proverava se da su zadate putanje fajlova putem argumenata
    komandne linije. */
    assert(argc == 3);

    /* Otvara se prvi fajl. */
    if ((file = open(argv[1], O_RDONLY)) < 0)
        error("open()");

    /* Otvara se drugi fajl. */
    if ((copy = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP)) < 0)
        error("open()");
    
    /* Ocitava se velicina prvog fajla. */
    if (fstat(file, &stats) < 0)
        error("fstat()");

    /* Prosiruje se drugi fajl na velicinu prvog fajla. */
    if (lseek(copy, stats.st_size - 1, SEEK_SET) < 0)
        error("lseek()");
    if (write(copy, " ", 1) != 1)
        error("write()");

    /* Memorijski se mapira prvi fajl. */
    if ((src = mmap(0, stats.st_size, PROT_READ, MAP_FILE | MAP_SHARED, file, 0)) == (caddr_t) -1)
        error("mmap()");

    /* Memorijski se mapira drugi fajl. */
    if ((dst = mmap(0, stats.st_size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, copy, 0)) == (caddr_t) -1)
        error("mmap()");

    /* Kopira se fajl. */
    memcpy(dst, src, stats.st_size);

    /* Oslobadja se alocirani prostor. */
    munmap(src, stats.st_size);
    munmap(dst, stats.st_size);

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
