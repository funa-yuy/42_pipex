/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:13:06 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/10 22:42:02 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	last_cmd(char **cmd, char **envp, int i)
{
	fprintf(stderr, "last_cmd関数:fork[%d]の子供です。実行コマンドは→%s\n", i, cmd[0]);

	// char c;
	// int count;
	// while ((count = read(pipe_fd_1[0], &c, 1)) > 0) {
	// 	putchar(c);
	// }

	fprintf(stderr, "korekara\n");
	execve(cmd[0], cmd, envp);
	error("last_cmd");
}

void	first_cmd(char **cmd, char **envp, int i)
{
	fprintf(stderr, "first_cmd関数:fork[%d]の子供です。実行コマンドは→%s\n", i, cmd[0]);

	fprintf(stderr, "korekara\n");
	execve(cmd[0], cmd, envp);
	error("first_cmd");
}

void	middle_cmd(char **cmd, char **envp, int i)
{
	fprintf(stderr, "middle_cmd関数:fork[%d]の子供です。実行コマンドは→%s\n", i, cmd[0]);

	fprintf(stderr, "korekara\n");
	execve(cmd[0], cmd, envp);
	error("middle_cmd");
}
