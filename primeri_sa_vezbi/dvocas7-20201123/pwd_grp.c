#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <errno.h>

/* Program demonstrira rad sa korisnicima i grupama. */

void error(char *message);

int main(int argc, char **argv){
    struct passwd *pwd;         /* Promenljiva za informacije o korisniku. */
    struct group *grp;          /* Promenljiva za informacije o grupi. */
    gid_t gid;                  /* Promenljiva za informaciju o grupi. */
    char *shell;                /* Promenljiva za shell. */

    /* Proverava se da li postoje dva argumenta komandne linije. */
    assert(argc == 2);

    /* Pronalaze se informacije o datom korisniku. */
    if ((pwd = getpwnam(argv[1])) == NULL)
        error("getpwnam()");

    /* Ispisuju se informacije o datom korisniku. */
    printf("Name:\t%s\n", pwd->pw_name);
    printf("UID:\t%d\n", pwd->pw_uid);

    /* Pronalazi se ime grupe na osnovu gid-a. */
    if ((grp = getgrgid(pwd->pw_gid)) == NULL)
        error("getgrgid()");
    
    /* Ispisuje se ime grupe. */
    printf("Group:\t%s\n", grp->gr_name);
    printf("Home:\t%s\n", pwd->pw_dir);
    printf("Shell:\t%s\n", pwd->pw_shell);

    /* Cuvaju se vrednosti promenljivih koje su potrebne za dalji
    tok programa zato sto ce funkcije za informacije o korisnicima
    da promene njihovu vrednost. */
    gid = pwd->pw_gid;
    if ((shell = malloc((strlen(pwd->pw_shell) + 1) * sizeof(char))) == NULL)
        error("malloc()");
    strcpy(shell, pwd->pw_shell);

    /* Ispisuju se imena svih korisnika kojima je inicijalna grupa
    ista kao i datom korisniku. */
    setpwent();

    printf("Users in group %s:\n", grp->gr_name);
    errno = 0;
    for(;(pwd = getpwent()) != NULL;){
        if (pwd->pw_gid == gid)
            printf("%s\n", pwd->pw_name);
    }

    if (errno != 0)
        error("getpwent()");

    endpwent();

    /* Ispisuju se imena svih korisnika koji imaju podrazumevani
    shell isti kao i dati korisnik. */
    setpwent();

    printf("Shell %s:\n", shell);
    errno = 0;
    for (;(pwd = getpwent()) != NULL;){
        if (!strcmp(pwd->pw_shell, shell))
            printf("%s\n", pwd->pw_name);
    }

    if (errno != 0)
        error("getpwent()");

    endpwent();

    /* Zavrsava se program. */
    exit(EXIT_SUCCESS);
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}
