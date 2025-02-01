/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:50:55 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/01 21:22:55 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// ./a.out infile "ls -l" "wc -l" outfile

void	error(char *msg)
{
	perror(msg);
	exit(1);
}

int	main(int argc, char *argv[], char **envp)
{
	int 	filedes[2];
	char	**pargv;
	char	**cargv;
	pid_t	pid;
	char	**cmd;
	char	**cmd_2;
	int		i;

	// if (argc != 5)
	// 	return (0);

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
		// char c;
		// int count;
		// while ((count = read(filedes[0], &c, 1)) > 0) {
		// putchar(c);
		// }
		close(0);
		if (dup2(filedes[0], 0) < 0)
			exit(1);
		close(filedes[0]);

		cmd_2 = ft_split(argv[3], ' ');
		i = 0;
		while (cmd_2[i] != NULL)
			i++;
		pargv = malloc(i + 2 * sizeof(char *));
		i = 0;
		while (cmd_2[i] != NULL)
		{
			pargv[i] = cmd_2[i];
			printf("%s \n", cmd_2[i]);
			i++;
		}
		pargv[i] = NULL;
		// pargv[0] = "wc";
		// pargv[1] = "-l";
		// pargv[2] = NULL;
		execve("/usr/bin/wc", pargv, envp);
		free(cmd_2);
		free(pargv);
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
		cmd = ft_split(argv[2], ' ');
		i = 0;
		while (cmd[i] != NULL)
			i++;
		cargv = malloc(i + 2 * sizeof(char *));
		i = 0;
		while (cmd[i] != NULL)
		{
			cargv[i] = cmd[i];
			printf("%s \n", cmd[i]);
			i++;
		}
		cargv[i] = argv[1];
		cargv[i + 1] = NULL;
		execve("/bin/ls", cargv, envp);
		free(cmd);
		free(cargv);
		error("ls failed");
	}
	return (0);
}
