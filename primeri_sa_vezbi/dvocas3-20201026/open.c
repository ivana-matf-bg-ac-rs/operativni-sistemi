#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

/* Program demonstrira koriscenje fajl deskriptora, open i close
funkcija. */

void error(char *message);

int main(int argc, char **argv){
	int fd;		/* Fajl deskriptor */

	/* Ispisuju se vrednosti konstanti za standardni ulaz,
	standardni izlaz i standardnu gresku. */
	fprintf(stdout, "STDIN_FILENO = %d\n", STDIN_FILENO);
	fprintf(stdout, "STDOUT_FILENO = %d\n", STDOUT_FILENO);
	fprintf(stdout, "STDERR_FILENO = %d\n", STDERR_FILENO);

	/* Pokusava se sa otvaranjem fajla koji ne postoji. */
	if ((fd = open("f1.txt", O_RDWR)) < 0){
		error("open()");
	}else{
		fprintf(stdout, "Fajl deskriptor: %d\n", fd);	
	}

	/* Pokusava se sa zatvaranjem fajl deskriptora. */
	if (close(fd) < 0){
		error("close()");
	}
	
	/* Pokusava se sa otvaranjem fajla koji ne postoji uz
	O_CREAT fleg. */
	if ((fd = open("f1.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH)) < 0){
		error("open()");
	}else{
		fprintf(stdout, "Fajl deskriptor: %d\n", fd);	
	}

	/* Pokusava se sa zatvaranjem fajl deskriptora. */
	if (close(fd) < 0){
		error("close()");
	}
	
	/* Zavrsava se program. */
	exit(EXIT_SUCCESS);
}

void error(char *message){
	perror(message);
	exit(EXIT_FAILURE);
}

