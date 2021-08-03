#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	int i;

	for (i = 1; i < argc; i++) {
		FILE *f;
		int c; 
		int line = 0;

		f = fopen(argv[i], "r");
		if (!f) {
			perror(argv[i]);
			exit(1);
		}
		while ((c = fgetc(f)) != EOF) {
			//if (putchar(c) < 0) exit(0);
			if (c == '\n') line = line + 1;
		}
		fclose(f);
		printf("%d\n", line);
	}
	exit(0);
}
