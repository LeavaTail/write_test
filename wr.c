#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PROGRAMNAME     "wr"
#define MAXSIZE         10737418240  // 10GB

static inline void usage ()
{
	fprintf(stdout, "%s FILE BUFSIZE\n", PROGRAMNAME);
}

int main (int argc, char **argv)
{
	FILE *fp;
	int loop = 0;
	int number = 0;
	int count = 0;
	int c = ' ';
	int ret = EXIT_FAILURE;

	if (argc != 3) {
		usage();
		exit(EXIT_FAILURE);
	}

	if ((fp = fopen(argv[1], "ab+")) == NULL) {
		perror("Open output file ");
		exit(EXIT_FAILURE);
	}

	for (c = ' '; c <= '~'; c++) {
		for(loop = 0; loop < atol(argv[2]); loop++) {
			if ((fputc(c, fp)) == EOF)
				goto out;
		}
	}

	ret = EXIT_SUCCESS;
out:
	fclose (fp);
	return ret;
}
