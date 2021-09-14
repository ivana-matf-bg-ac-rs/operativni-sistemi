#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 1000000

/* Program demonstira neblokirajuci rezim za 
standardni izlaz. */

void error(char *message);

int main(int argc, char **argv){
    char buffer[BUFFER_SIZE];       /* Bafer za razmenu poruka. */
    char *curr;                     /* Tekuca pozicija u gornjem baferu. */
    int left;                       /* Broj bajtova koji treba da budu ispisani. */
    int written;                    /* Broj bajtova koji je ispisan u jednom pozivu write
                                    funkcije. */
    int flags;                      /* Promenljiva za flegove standardnog izlaza. */

    /* Ucitavaju se podaci sa standardnog ulaza. */
    if ((left = read(STDIN_FILENO, buffer, BUFFER_SIZE)) < 0)
        error("read()");

    /* Postavlja se O_NONBLOCK fleg na standardni izlaz. */
    if ((flags = fcntl(STDOUT_FILENO, F_GETFL, 0)) < 0)
        error("fcntl()");
    flags |= O_NONBLOCK;
    if ((flags = fcntl(STDOUT_FILENO, F_SETFL, flags)) < 0)
        error("fcntl()");

    /* Ispisuju se podaci iz bafera na standardni izlaz. */
    for(curr = buffer; left > 0;){
        errno = 0;
        written = write(STDOUT_FILENO, curr, left);
        fprintf(stderr, "written %d bytes, errno = %d\n", written, errno);
        if (written > 0){
            curr += written;
            left -= written;
        }
    }

    /* Iskljucuje se O_NONBLOCK fleg. */
    flags &= ~O_NONBLOCK;
    if ((flags = fcntl(STDOUT_FILENO, F_SETFL, flags)) < 0)
        error("fcntl()");

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
