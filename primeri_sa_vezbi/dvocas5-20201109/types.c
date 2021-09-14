#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* Program ispituje kog su tipa fajlovi cije su putanje
zadate argumentima komandne linije. */

void error(char *message);

int main(int argc, char **argv){
    int i;                  /* Iterator kroz argumente komandne linije. */
    struct stat stats;      /* Struktura za informacije o fajlu. */

    /* Za svaki argument komandne linije... */
    for (i=0; i<argc; i++){
        /* ... ocitavaju se informacije o fajlu... */
        if (lstat(argv[i], &stats) < 0)
            error("stat()");
        
        /* ... i ispituje se kog je tipa. */
        if (S_ISREG(stats.st_mode))
            printf("Regularni fajl.\n");
        else if (S_ISDIR(stats.st_mode))
            printf("Direktorijum.\n");
        else if (S_ISCHR(stats.st_mode))
            printf("Karakterski specijalni fajl.\n");
        else if (S_ISBLK(stats.st_mode))
            printf("Blokovski specijalni fajl.\n");
        else if (S_ISLNK(stats.st_mode))
            printf("Simbolicki link.\n");
        else if (S_ISSOCK(stats.st_mode))
            printf("Soket.\n");
        else if (S_ISFIFO(stats.st_mode))
            printf("FIFO.\n");
        else
            printf("Nepoznati tip.\n");
    }

    /* ZaVrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}