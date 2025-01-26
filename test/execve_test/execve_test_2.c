/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:50:55 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/26 17:07:45 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	(void)argc;
	extern char	**environ;
	int filedes[2];
	char		*pargv[2];
	char		*cargv[2];
	pid_t		pid;

	if (pipe(filedes) < 0)
		exit(1);

	if (pid = fork() < 0)
		exit(1);

	if (pid > 0)
	{
		if (close(filedes[0]) == -1)
			exit(1);
		pargv[0] = "wc";
		pargv[1] = NULL;
		execve("/bin/wc", pargv, environ);
		wait(NULL);
	}
	else if (pid == 0)
	{
		if (close(filedes[1]) == -1)
			exit(1);
		cargv[0] = "ls";
		cargv[1] = NULL;
		execve("/bin/ls", cargv, environ);

	}

		if (pid = fork() < 0)
		exit(1);

	if (pid > 0)
	{
		if (close(filedes[0]) == -1)
			exit(1);
		pargv[0] = "wc";
		pargv[1] = NULL;
		execve("/bin/wc", pargv, environ);
		wait(NULL);
	}
	else if (pid == 0)
	{
		if (close(filedes[1]) == -1)
			exit(1);
		cargv[0] = "ls";
		cargv[1] = NULL;
		execve("/bin/ls", cargv, environ);

	}

	return (0);
}
