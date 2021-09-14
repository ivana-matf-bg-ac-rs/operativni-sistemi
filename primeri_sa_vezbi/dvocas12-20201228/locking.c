#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define LOCK_FILE "file.lock"

/* Program demonstrira zakljucavanje fajla i nemogucnost da 
dve instance programa zakljucaju isti fajl za pisanje u 
ustom trenutku. */

void error(char *message);

int main(int argc, char **argv){
    int file;               /* Fajl deskriptor fajla koji se zakljucava. */
    struct flock lock;      /* Struktura koja opsuje lock. */

    /* Otvara se fajl za pisanje. Ako ne postoji, kreira se. */
    if ((file = open(LOCK_FILE, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
        error("open()");

    /* Zakljucava se fajl za pisanje. */
    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    if (fcntl(file, F_SETLK, &lock) < 0){
        if (errno == EACCES || errno == EAGAIN){
            printf("another instance already running\n");
            exit(EXIT_SUCCESS);
        }else
            error("fcntl()");
    }

    /* Ispisuje se poruka. */
    printf("file locked\n");

    /* Uspavljuje se proces na 10 sekundi. */
    sleep(10);

    /* Otkljucava se fajl. */
    lock.l_type = F_UNLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    if (fcntl(file, F_SETLK, &lock) < 0)
        error("fcntl()");

    /* Ispisuje se poruka. */
    printf("file unlocked\n");

    /* Uspavljuje se proces na 10 sekundi. */
    sleep(10);

    /* Zavrsava se proces. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
