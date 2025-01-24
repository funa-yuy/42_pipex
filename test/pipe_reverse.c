#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>

int pipe_fd[2];

void do_parent(void)
{
	char c;
	int count;
	int status;

	printf("This is parent.\n");

	close(pipe_fd[1]);

	while ((count = read(pipe_fd[0], &c, 1)) > 0) {
		putchar(c);
	}
	if (count < 0) {
		perror("read");
		exit(1);
	}

	if (wait(&status) < 0) {
		perror("wait");
		exit(1);
	}
	close(pipe_fd[0]);
}

void do_child(void)
{

	char *p = "Hello, my kid.";

	printf("This is child.\n");

	close(pipe_fd[0]);
	while (*p != '\0') {
		if (write(pipe_fd[1], p, 1) < 0) {
				perror("write");
				exit(1);
		}
		p++;
	}

	close(pipe_fd[1]);
}

int	main(void)
{
	int	child;

	if (pipe(pipe_fd) < 0) {
			perror("pipe");
			exit(1);
	}

	if ((child = fork()) < 0) {
			perror("fork");
			exit(1);
	}

	if (child) {
			do_parent();
	} else {
			do_child();
	}

	return EXIT_SUCCESS;
}
