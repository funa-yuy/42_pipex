/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:50:55 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/28 18:25:16 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

//ls | wc

void	error(char *msg)
{
	perror(msg);
	exit(1);
}

int	main(int argc, char *argv[])
{
	(void)argc;
	extern char	**environ;
	int filedes[2];
	char		*pargv[2];
	char		*cargv[3];
	pid_t		pid;

	if (argc != )
	if (pipe(filedes) < 0)
		error("pipe(filedes)");
	pid = fork();
	if (pid < 0)
		error("pid < 0");

	if (pid > 0)
	{
		if (close(filedes[1]) == -1)
			error("lose(filedes[1])");
		wait(NULL);
		close(0);
		if (dup2(filedes[0], 0) < 0)
			exit(1);
		close(filedes[0]);
		pargv[0] = "wc";
		pargv[1] = NULL;
		execve("/usr/bin/wc", pargv, environ);
		error("wc failed");
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
		error("ls failed");
	}
	return (0);
}
