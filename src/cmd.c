/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:13:06 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/07 20:13:25 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libft/libft.h"

int	last_cmd(char *argv[], char **envp, int pipe_fd[3], int i)
{
	char	*pargv[3];

	printf("last_cmd関数:fork[%d]の子供です。実行コマンドは→%s\n", i, argv[i + 1]);

	// char c;
	// int count;
	// while ((count = read(pipe_fd_1[0], &c, 1)) > 0) {
	// 	putchar(c);
	// }
	close(pipe_fd[0]);
	close(pipe_fd[3]);
	if (close(pipe_fd[1]) == -1)
		error("lose(pipe_fd[1])");
	if (close(0) == -1)
		error("close");
	if (dup2(pipe_fd[2], 0) < 0)
		error("dup");
	if (close(pipe_fd[2]) == -1)
		error("close");

	pargv[0] = argv[i + 1];
	pargv[1] = "5";
	pargv[2] = NULL;
	execve(pargv[0], pargv, envp);
	error("wc failed");
}

void	first_cmd(char *argv[], char **envp, int pipe_fd[3], int i)
{
	char	*cargv[2];

	close(pipe_fd[2]);
	close(pipe_fd[3]);
	if (close(pipe_fd[0]) == -1)
		error("close(pipe_fd[0])");

	if (close(1) == -1)
		error("close");
	if (dup2(pipe_fd[1], 1) < 0)
		error("dup");
	if (close(pipe_fd[1]) == -1)
		error("close");
	cargv[0] = argv[i + 1];
	cargv[1] = NULL;
	execve(cargv[0], cargv, envp);
	error("ls failed");
}

void	middle_cmd(char *argv[], char **envp, int pipe_fd[3], int i)
{
	char	*cargv[2];

	printf("middle_cmd関数:fork[%d]の子供です。実行コマンドは→%s\n", i, argv[i + 1]);

	// char c;
	// int count;
	// while ((count = read(pipe_fd[0], &c, 1)) > 0) {
	// 	putchar(c);
	// }
	if (close(pipe_fd[1]) == -1)
		error("close(pipe_fd[0])");
	if (close(pipe_fd[2]) == -1)
		error("close(pipe_fd[0])");

	if (close(0) == -1)
		error("close");
	if (dup2(pipe_fd[0], 0) < 0)
		error("dup");
	if (close(pipe_fd[0]) == -1)
		error("close");

	if (close(1) == -1)
		error("close");
	if (dup2(pipe_fd[3], 1) < 0)
		error("dup");
	if (close(pipe_fd[3]) == -1)
		error("close");

	cargv[0] = argv[i + 1];
	cargv[1] = NULL;
	execve(cargv[0], cargv, envp);
	error("wc failed");
}
