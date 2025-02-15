/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:13:06 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/15 21:17:59 by miyuu            ###   ########.fr       */
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

void	error_cmd_not_found(char *cmd)
{
	char	*error_msg;

	error_msg = ": command not found\n";
	write(2, cmd, ft_strlen(cmd));
	write(2, error_msg, ft_strlen(error_msg));
}

void	execute_cmd(char **cmds, char **envp)
{
	if (access(cmds[0], F_OK) == -1)
	{
		if (ft_strchr (cmds[0], '/') == NULL)
			error_cmd_not_found(cmds[0]);
		else
		{
			write(2, cmds[0], ft_strlen(cmds[0]));
			write(2, ": ", 2);
			perror(NULL);
		}
		exit(127);
	}
	execve(cmds[0], cmds, envp);
	write(2, cmds[0], ft_strlen(cmds[0]));
	write(2, ": ", 2);
	perror(NULL);
	exit(126);
}
