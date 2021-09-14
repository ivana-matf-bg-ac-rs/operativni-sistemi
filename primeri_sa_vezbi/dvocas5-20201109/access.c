#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* Program demonstrira razliku izmedju realnog i efektivnog Id-a. */

void error(char *message);

int main(int argc, char **argv){
    /* Proverava se da li fajl moze da se otvori za pisanje
    pomocu realnog Id-a. */
    if (access("foo", W_OK) < 0)
        printf("Ne moze da se pristupi na osnovu realnog Id-a.\n");
    else
        printf("Moze da se pristupi na osnovu realnog Id-a.\n");
    

    /* Proverava se da li fajl moze da se otvori za pisanje
    pomocu efektivnog Id-a. */
    if (open("foo", O_WRONLY) < 0)
        printf("Ne moze da se pristupi na osnovu efektivnog Id-a.\n");  
    else
        printf("Moze da se pristupi na osnovu efektivnog Id-a.\n");  

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
