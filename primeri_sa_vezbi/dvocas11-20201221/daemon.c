#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>

void error(char *message);

void deamonize();

int main(int argc, char **argv){
    /* Postavlja se da program bude deamon, ondosno da nema
    terminal koji ga kontrolise. */
    deamonize();

    /* Uspavljuse se proces na odredjeni broj sekundi. */
    sleep(10);

    /* Zavrsava se proces. */
    exit(EXIT_SUCCESS);
}

void deamonize(){
    int i, fd0, fd1, fd2;           /* Pomocne promenljive. */
    pid_t pid;                      /* Promenljiva za id procesa. */
    struct rlimit rl;               /* Promenljiva za informacije o maksimalnom broju
                                    orvorenih fajl deskriptora. */

    /* Brise se nasledjena umask vrednost. */
    umask(0);

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        error("getrlimit()");

    /* Potrebno je napraviti child proces koji ce postati
    lider sesije kako bi mogao da se oslobodi terminala
    koji ga kontrolise. */
    if ((pid = fork())< 0)
        error("fork()");
    else if (pid != 0)
        exit(EXIT_SUCCESS);

    setsid();

    if ((pid = fork()) < 0)
        error("fork()");
    else if (pid != 0)
        exit(EXIT_SUCCESS);
    
    /* Zatvaraju se otvoreni fajl desktoptori. */
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (i=0; i<rl.rlim_max; i++)
        close(i);

    /* Premesta se u "/" direktoriju. */
    if (chdir("/") < 0)
        error("chdir()");

    /* Preusmerava se sadrzaj koji se posalje na 0, 1 i 2 na /dev/null. */
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    /* Inicijalizuje se log fajl. */
    openlog("deamon", LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2){
        syslog(LOG_ERR, "unexpected file descriptors: %d, %d, %d\n", fd0, fd1, fd2);
        //exit(EXIT_FAILURE);
    }else{
        syslog(LOG_INFO, "file descriptors OK");
        //exit(EXIT_SUCCESS);
    }
}

void error(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}