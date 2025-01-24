#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int	main()
{
	pid_t	pid;
	char	buf[256];
	int	pp[2];

	pipe(pp);

	pid = fork();

	// while(1)
	// {
		if (pid > 0)
		{
			close(pp[1]);
			read(pp[0], buf, 256);
			printf("Msg Child: %s", buf);
			close(pp[0]);
		}
		else if (pid == 0)
		{
			close(pp[0]);
			printf("Msg Parent:");
			fgets(buf, 256, stdin);
			write(pp[1], buf, strlen(buf) + 1);
			close(pp[1]);
			while (1)
				;
		}
		else
		{
			exit(1);
		}
	// }

	return (0);
}
