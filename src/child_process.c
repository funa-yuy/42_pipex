/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:13:06 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/15 22:17:54 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// void	child_process(t_pipex data, int input_fd, int *current_pipe, int i)
// {
// 	int	outfile_fd;

// 	if (i == 0)
// 	{
// 		input_fd = open(data.infile, O_RDWR);
// 		if (input_fd == -1)
// 			error(NULL);
// 	}

// 	dup2(input_fd, STDIN_FILENO);
// 	close(input_fd);

// 	if (i != data.cmd_num - 1) {
// 		// 次のパイプの書き込みを標準出力に設定
// 		dup2(current_pipe[1], STDOUT_FILENO);
// 		close(current_pipe[1]);
// 		close(current_pipe[0]);
// 	}

// 	if (i == data.cmd_num - 1)
// 	{
// 		outfile_fd = open(data.outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 		if (outfile_fd == -1)
// 			error(NULL);
// 		dup2(outfile_fd, STDOUT_FILENO);
// 		close(outfile_fd);
// 	}
// }

void	setup_input_fd(t_pipex data, int input_fd, int *current_pipe, int i)
{
	if (i == 0)
	{
		input_fd = open(data.infile, O_RDWR);
		if (input_fd == -1)
			error(NULL);
	}
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
}

void	setup_output_fd(t_pipex data, int *current_pipe, int i)
{
	int	outfile_fd;

	if (i == data.cmd_num - 1)
	{
		outfile_fd = open(data.outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (outfile_fd == -1)
			error(NULL);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
	}
	else
	{
		dup2(current_pipe[1], STDOUT_FILENO);
		close(current_pipe[1]);
		close(current_pipe[0]);
	}
}

void	child_process(t_fd *fd_data, t_pipex data, char **cmd, char **envp, int i)
{
	int	outfile_fd;

	setup_input_fd(data, fd_data->input_fd, fd_data->current_pipe, i);
	setup_output_fd(data, fd_data->current_pipe, i);
	execute_cmd(cmd, envp);
}


void	error_write_str_colon(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
}

void	error_cmd_not_found(char *cmd)
{
	char	*error_msg;

	error_msg = "command not found\n";
	write(2, error_msg, ft_strlen(error_msg));
}

void	execute_cmd(char **cmd, char **envp)
{
	if (access(cmd[0], F_OK) == -1)
	{
		error_write_str_colon(cmd[0]);
		if (ft_strchr (cmd[0], '/') == NULL)
			error_cmd_not_found(cmd[0]);
		else
			perror(NULL);
		exit(127);
	}
	if (execve(cmd[0], cmd, envp) < 0)
	{
		error_write_str_colon(cmd[0]);
		perror(NULL);
		exit(126);
	}
}
