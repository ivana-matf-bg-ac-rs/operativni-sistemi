#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define COUNT 10000

/* Funkcija za obradu greske. */
void error(char *message);

/* Funkcija koja predstavlja nit. */
void *thread(void *arg);

/* Funkcija koja predstavlja child proces. */
void child(void);

/* Program demonstrira razliku u vremenu izvrsavanja niti i
child procesa. */
int main(int argc, char **argv){
    int threads;            /* Indikator koji odredjuje da li treba da se
                            kreiraju niti ili procesi. */
    int i;                  /* Brojac u petlji. */

    /* Proverava se da li postoje dva argumenta komandne linije. */
    assert(argc == 2);

    if (!strcmp(argv[1], "p"))
        threads = 0;
    else if (!strcmp(argv[1], "t"))
        threads = 1;
    else
        error("Wrong input.");

    if (threads){
        pthread_t tid;          /* Promenljiva za id niti. */
        pthread_attr_t attr;    /* Atributi niti. */

        /* Inicijalizuju se atributi niti. */
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        /* U petlji se kreira odredjeni broj niti. */
        for (i=0; i<COUNT; i++){
            pthread_create(&tid, &attr, thread, NULL);
            pthread_join(tid, NULL);
        }

        /* Unistavaju se atributi niti. */
        pthread_attr_destroy(&attr);
    }else{
        pid_t pid;              /* Promenljiva za id procesa. */
        
        /* U petlji se kreira odredjeni broj child procesa. */
        for (i=0; i<COUNT; i++){
            if ((pid = fork()) < 0)
                error("fork()");
            else if (pid == 0){
                child();
            }else{
                waitpid(pid, NULL, 0);
            }
        }
    }

    /* Zavrsava se proces. */
    exit(EXIT_SUCCESS);
}

void *thread(void* arg){
    int temp;           /* Deklarise se promenljiva. */

    /* Dodeljuje se vrednosti promenljivoj. */
    temp = 1;

    /* Zavrsava se nit. */
    pthread_exit(NULL);
}

void child(){
    int temp;           /* Deklarise se promenljiva. */

    /* Dodeljuje se vrednost promenljivoj. */
    temp = 1;

    /* Zavrsava se proces. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
