/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:13:06 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/14 20:51:51 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(t_pipex data, int input_fd, int *current_pipe, int i)
{
	int	outfile_fd;

	if (i == 0)
	{
		input_fd = open(data.infile, O_RDWR);
		if (input_fd == -1)
			error(NULL);
	}
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);

	if (i != data.cmd_num - 1) {
		// 次のパイプの書き込みを標準出力に設定
		dup2(current_pipe[1], STDOUT_FILENO);
		close(current_pipe[1]);
		close(current_pipe[0]);
	}

	if (i == data.cmd_num - 1)
	{
		outfile_fd = open(data.outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (outfile_fd == -1)
			error(NULL);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
	}
}

void	execute_cmd(char **cmds, char **envp)
{
	execve(cmds[0], cmds, envp);
	perror("execve failed");
	exit(126);
}
