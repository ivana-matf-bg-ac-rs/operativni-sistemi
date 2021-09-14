#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int n;          /* Duzina vektora. */
    float *x, *y;   /* Adrese vektora. */    
} Data;             /* Struktura podatka koja se prenosi niti kao argument. */

static float dot_product;       /* Vrednosti skalarnog proizvoda. */
static pthread_mutex_t mutex;   /* Mutex kojim se zakljucava kriticna sekcija, odnosno
                                pristup gornjoj promenljivoj. */

void *run(void *arg);           /* Funkcija koja predstavlja nit. */

void error (char *message);     /* Funkcija za obradu greske. */

/* Program demonstrira sinhronizovani pristup promenljivoj
prilikom racunanja skalarnog proizvoda. */
int main(int argc, char **argv){
    int n;              /* Velicina vektora. */
    float *x, *y;       /* Adrese vektora. */
    int count;          /* Broj niti koje treba napraviti. */
    pthread_t *threads; /* Niz id-eva niti koje se prave. */
    Data *data;         /* Niz za strukture sa podacima koji se
                        prosledjuju nitima. */
    pthread_attr_t attr;        /* Atributi niti. */
    int i;              /* Brojac u petljama. */

    /* Ucitava se dimenzija vektora. */
    scanf("%d", &n);

    /* Proverava se da li je ucitana ispravna dimenzija. */
    assert(n > 0);

    /* Alociraju se prostori za vektore. */
    if ((x = (float *) malloc(n * sizeof(float))) == NULL)
        error("malloc()");
    if ((y = (float *) malloc(n * sizeof(float))) == NULL)
        error("malloc()");

    /* Ucitavaju se elementi vektora. */
    for (i=0; i<n; i++)
        scanf("%f%f", &x[i], &y[i]);

    /* Ucitava se broj niti. */
    scanf("%d", &count);

    /* Proverava se da li je zadat ispravan broj niti. */
    assert(count > 0 && n%count == 0);

    /* Alocira se prostor za id niti. */
    if ((threads = (pthread_t *) malloc(count * sizeof(pthread_t))) == NULL)
        error("malloc()");

    /* Alocira se prostor za podatke koji se prosledjuju svakoj niti. */
    if ((data = (Data *) malloc(count * sizeof(Data))) == NULL)
        error("malloc()");

    /* Inicijalizuje se skalarni proizvod na nulu. */
    dot_product = 0;

    /* Inicijalizuje se mutex. */
    pthread_mutex_init(&mutex, NULL);

    /* Inicijalizuju se atributi niti. */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    /* U petlji se deli vektor na count delova i za svaki deo
    se kreira se po jedna nit koja ce izracunati odgovarajuci 
    parcijalni skalarni proizvod. */
    int nc = n/count;
    for (i=0; i<count; i++){
        data[i].n = nc;
        data[i].x = x + i * nc;
        data[i].y = y + i * nc;
        pthread_create(&threads[i], &attr, run, &data[i]);
    }

    /* Unistavaju se atributi niti. */
    pthread_attr_destroy(&attr);

    /* Ceka se da se izvrse sve niti. */
    for (i=0; i<count; i++)
        pthread_join(threads[i], NULL);

    /* Oslobadja se dinamicki alocirana memorija. */
    free(x);
    free(y);
    free(threads);
    free(data);

    /* Unistava se mutex. */
    pthread_mutex_destroy(&mutex);

    /* Ispisuje se skalarni proizvod. */
    printf("%g\n", dot_product);

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void *run(void *arg){
    Data *data;         /* Podaci koji su dobijeni preko argumenta. */
    float sum;          /* Parcijalna suma. */
    int i;              /* Brojac u petlji. */

    /* Kastuje se argument u odgovarajuci tip. */
    data = (Data *) arg;

    /* Inicijalizuje se suma. */
    sum = 0;

    /* Izracunava se parcijalna suma. */
    for (i=0; i<data->n; i++)
        sum += data->x[i] * data->y[i];

    /* Dodaje se parcijalna suma na glavni proizvod. */
    pthread_mutex_lock(&mutex);
    dot_product += sum;
    pthread_mutex_unlock(&mutex);

    /* Zavrsava se nit. */
    pthread_exit(NULL);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
