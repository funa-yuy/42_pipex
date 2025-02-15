/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_setup_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:33:25 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/15 22:46:00 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	setup_input_fd(t_pipex data, int input_fd, int *current_pipe, int i)
{
	if (i == 0)
	{
		input_fd = open(data.infile, O_RDWR);
		if (input_fd == -1)
			error(data.infile);
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
