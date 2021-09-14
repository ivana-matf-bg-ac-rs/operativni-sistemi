#include <stdio.h>
#include <string.h>
#include <errno.h>

/* Program demonstrira rad sa errno vrednoscu. */

int main(int argc, char **argv){
	fprintf(stdout, "Greska: %s\n", strerror(EACCES));

	errno = ENOENT;

	fprintf(stdout, "Greska: %s\n", strerror(errno));

	perror("Greska1");
}
