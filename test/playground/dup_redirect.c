#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

//argv[1]ファイルを"wc"するプログラム

int	main(int argc, char *argv[])
{
	(void)argc;
	extern char	**environ;
	int		fd;
	char	*exeargv[2];

	if (argc != 2)
		exit(1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit(1);
	close(0);

	if (dup2(fd, 0) < 0)
		exit(1);
	close(fd);
	exeargv[0] = "wc";
	exeargv[1] = NULL;

	execve("/bin/wc", exeargv, environ);

	return (0);
}
