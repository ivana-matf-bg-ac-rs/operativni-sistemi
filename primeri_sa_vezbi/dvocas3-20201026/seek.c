#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* Program ispituje da li je fajl vezan za standardni ulaz
pretraziv. */

int main(int argc, char **argv){
	if (lseek(STDIN_FILENO, 0, SEEK_CUR) < 0){
		perror("lseek()");
	}else{
		fprintf(stdout, "Moze da se pretrazuje.\n");
	}

	exit(EXIT_SUCCESS);
}
