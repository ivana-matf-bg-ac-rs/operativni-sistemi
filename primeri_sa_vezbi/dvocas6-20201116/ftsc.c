#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

/* Program rekurzivno obilazi direktorijum cije je putanja data kao
argument komandne linije i racuna koliko se fajlova kog tipa
pojavilo pri obilasku. */

typedef struct {
    int regular_count;
    int directory_count;
    int character_count;
    int block_count;
    int fifo_count;
    int symlink_count;
    int socket_count;
    int total_count;
} Statistics;

void error(char *message);

void traverse(char *file, void *data);

int main(int argc, char **argv){
    Statistics statistics = {0, 0, 0, 0, 0, 0, 0, 0};          /* Promenljiva za informacije o broju fajlova. */

    /* Proverava se da postoji argument komandne linije. */
    assert(argc == 2);

    /* Poziva se rekurzivni obilazak datog direktorijuma. */
    traverse(argv[1], &statistics);

    /* Ispisuju se izracunate vrednosti na izlaz. */
    if (statistics.total_count != 0){
        printf("regular count: %.2f%%\n", 100.0 * statistics.regular_count / statistics.total_count);
        printf("directory count: %.2f%%\n", 100.0 * statistics.directory_count / statistics.total_count);
        printf("character count: %.2f%%\n", 100.0 * statistics.character_count / statistics.total_count);
        printf("block count: %.2f%%\n", 100.0 * statistics.block_count / statistics.total_count);
        printf("fifo count: %.2f%%\n", 100.0 * statistics.fifo_count / statistics.total_count);
        printf("symlink count: %.2f%%\n", 100.0 * statistics.symlink_count / statistics.total_count);
        printf("socket count: %.2f%%\n", 100.0 * statistics.socket_count / statistics.total_count);
    }

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void traverse(char *file, void *data){
    struct stat stats;          /* Struktura za informacije o fajlu. */
    DIR *dp;                    /* Promenljiva koja predstavlja otvoreni direktorijum. */
    struct dirent *entry;       /* Promenljiva za clanove direktorijuma. */

    /* Ocitavaju se informacije o fajlu. */
    if (lstat(file, &stats) < 0)
        error("lstat()");

    if (S_ISREG(stats.st_mode)){
        ((Statistics *)data) -> regular_count++;
    }else if (S_ISCHR(stats.st_mode)){
        ((Statistics *)data) -> character_count++;
    }else if (S_ISBLK(stats.st_mode)){
        ((Statistics *)data) -> block_count++;
    }else if (S_ISLNK(stats.st_mode)){
        ((Statistics *)data) -> symlink_count++;
    }else if (S_ISFIFO(stats.st_mode)){
        ((Statistics *)data) -> fifo_count++;
    }else if (S_ISSOCK(stats.st_mode)){
        ((Statistics *)data) -> socket_count++;
    }else if (S_ISDIR(stats.st_mode)){
        ((Statistics *)data) -> directory_count++;

        /* Otvara se direktorijum. */
        if ((dp = opendir(file)) == NULL)
            error("opendir()");

        /* Prelazi se u direktorijum "file". */
        if (chdir(file) < 0)
            error("chdir()");

        /* Cita se sadrzaj direktorijuma... */
        for (;(entry = readdir(dp)) != NULL;){
            /* pri cemu se preskacu tekuci i roditeljski direktorijumi. */
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
                continue;

            /* rekurzivno se obilazi tekuci fajl. */
            traverse(entry->d_name, data);
        }

        /* Vraca se u pocetni direktorijum. */
        if (chdir("..") < 0)
            error("chdir()");

        /* Zatvara se direktorijum. */
        if (closedir(dp) < 0)
            error("closedir()");
    }


    /* Povecava se ukupan broj fajlova. */
    ((Statistics *)data) -> total_count++;
}


void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
