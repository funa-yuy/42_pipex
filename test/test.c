#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


// extern char	**environ;

// int	data0;
// int	data1 = 10;

// int	main(int argc, char *argv[])
// {
// 	(void)argc;
// 	char	c;

// 	printf("environ: \t%p\n", environ);
// 	printf("argv: \t%p\n", argv);
// 	printf("stack: \t%p\n", &c);

// 	printf("bss: \t%p\n", &data0);
// 	printf("data: \t%p\n", &data1);


// 	return (EXIT_SUCCESS);
// }


void	error(char *msg)
{
	perror(msg);
	exit(1);
}

int	main(int argc, char *argv[])
{
	// int	filedes[2];

	// if (pipe(filedes) == -1)
	// 	error("pipe");

	// pid_t pid = fork();
	// if (pid == 0)
	// {
	// 	// 出力口は不要なのでclose
	// 	if (close(filedes[1]) == -1)
	// 		error("close[1]");
	// 	printf("Child\n");
	// }
	// else if (pid > 0)
	// {
	// 	// 入力口は不要なのでclose
	// 	if (close(filedes[0]) == -1)
	// 		error("close[0]");
	// 	printf("Parent\n");
	// 	wait(NULL);
	// }
	// else
	// 	error("fork");

	(void)argc;
	int	file_fd;

	file_fd = open(argv[1], O_RDONLY);
	if (file_fd < 0)
		error("open");
	close(0);

	if (dup2(file_fd, 0) < 0)
	{
		error("dup2");
		close(file_fd);
	}
	close(file_fd);

	execlp("cat", "cat", NULL);

	return (0);
}
