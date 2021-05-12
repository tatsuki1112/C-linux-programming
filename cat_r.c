#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_cat(const char *path);
static void die(const char *s);
static void do_read();

int main(int argc, char *argv[])
{
	int i;
	if (argc < 2) {
		fprintf(stderr, "%s: file name not given\n", argv[0]);
		do_read();
		exit(1);
	}
	for (i = 1; 1 < argc; i++) {
		do_cat(argv[1]);
	}
	exit(0);

}

#define BUFFER_SIZE 2048

static void do_read()
{
	unsigned char buf[BUFFER_SIZE];
	int n;

	for (;;) {
		
		n = read(STDIN_FILENO, buf, sizeof buf);
		if (n < 0) exit(1);
		if (n == 0) break;
		if (write(STDOUT_FILENO, buf, n) < 0) exit(1);
	}
}

static void do_cat(const char *path)
{
	int fd;
	unsigned char buf[BUFFER_SIZE];
	int n;

	fd = open(path, O_RDONLY);
	if (fd < 0) die(path);
	for (;;) {
		n = read(fd, buf, sizeof buf);
		if (n < 0) die(path);
		if (n == 0) break;
		if (write(STDOUT_FILENO, buf, n) < 0) die(path);
	}
	if (close(fd) < 0) die(path);
}

static void die(const char *s)
{
	perror(s);
	exit(1);
}
