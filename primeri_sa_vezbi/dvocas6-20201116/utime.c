#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>
#include <fcntl.h>

/* Program za fajlove cije su putanje date argumentima 
komandne linije prvo ocitava stara vremena, zatim brise
sadrzaj fajlova i vraca stara vremena. */

void error(char *message);

int main(int argc, char **argv){
    struct stat stats;          /* Struktura za informacije o fajlu. */
    struct utimbuf times;       /* Struktura za vremena fajlova. */
    int i;                      /* Brojac u petlji. */
    int fd;                     /* Fajl deskriptor. */

    /* Za svaki fajl cija je putanja data argumentima komandne linije... */
    for (i=1; i<argc; i++){
        /* ...citaju se informacije o fajlu. */
        if (lstat(argv[i], &stats) < 0)
            error("lstat()");

        /* Otvara se fajl i brise se njegov sadrzaj. */
        if ((fd = open(argv[i], O_WRONLY | O_TRUNC)) < 0)
            error("open()");

        /* Zatvara se fajl. */
        if (close(fd) < 0)
            error("close()");

        times.actime = stats.st_atime;
        times.modtime = stats.st_mtime;

        /* Menjaju se vremena pristupa na prethodno ocitana. */
        if(utime(argv[i], &times) < 0)
            error("utime()");
    }

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
