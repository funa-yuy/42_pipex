#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

//"ls"の結果を、argv[2]ファイルに書き込むプログラム

void	error(char *msg)
{
	perror(msg);
	exit(1);
}

int	main(int argc, char *argv[])
{
	extern char	**environ;
	int		fd;
	int filedes[2];
	char		*cargv[3];
	pid_t		pid;


	if (argc < 2)
		error("argc > 2");

	if (pipe(filedes) < 0)
		error("pipe(filedes)");
	pid = fork();
	if (pid < 0)
		error("pid < 0");

	if (pid > 0)
	{
		char	buf;
		if (close(filedes[1]) == -1)
			error("lose(filedes[1])");
		wait(NULL);
		fd = open(argv[2], O_RDWR);
		if (fd < 0)
			error("open(argv[2], O_RDWR);");
		while (read(filedes[0], &buf, 1) > 0)
			write(fd, &buf, 1);
		if (close(filedes[0]) == -1)
			error("close(filedes[0])");
	}
	else if (pid == 0)
	{
		if (close(filedes[0]) == -1)
			error("close(filedes[0])");
		close(1);
		if (dup2(filedes[1], 1) < 0)
			exit(1);
		close(filedes[1]);
		cargv[0] = "ls";
		cargv[1] = argv[1];
		cargv[2] = NULL;
		execve("/bin/ls", cargv, environ);
		error("execve failed");
	}
	return (0);
}
