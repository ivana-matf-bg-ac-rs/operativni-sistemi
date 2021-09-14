#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* Program demonstrira rad sa funkcijama za vreme i datum. */

#define BUFFER_SIZE 256

void error(char *message);

int main(int argc, char **argv){
    time_t time_begin, time_end;          /* Promenljive za vreme. */
    struct tm *stm;                       /* Promenljiva za strukturirane informacije. */
    char buffer[BUFFER_SIZE];             /* Bafer za formatirani string. */

    /* Ocitava se tekuce vreme. */
    time(&time_begin);
    printf("time_begin = %ld\n", time_begin);

    /* Uspavljuje se proces na 5 sekundi. */
    sleep(5);

    /* Ponovo se ocitava tekuce vreme. */
    time(&time_end);

    /* Ispisuje se razlika u vremenu. */
    printf("time_end - time_begin = %ld\n", time_end - time_begin);

    /* Ispis datuma i vremena u predefinisanom formatu. */
    printf("ctime: %s\n", ctime(&time_begin));

    /* Popunjava se struktura sa informacijama o vremenu. */
    stm = localtime(&time_begin);

    /* Formira se string. */
    strftime(buffer, BUFFER_SIZE, "%F", stm);

    /* Ispisuje se formatirani string na izlaz. */
    printf("strftime: %s\n", buffer);

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
