/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_setup_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:33:25 by mfunakos          #+#    #+#             */
/*   Updated: 2025/03/06 14:15:15 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	setup_input_fd(t_pipex *data, int input_fd, int i)
{
	if (i == 0)
	{
		input_fd = open(data->infile, O_RDWR);
		if (input_fd == -1)
			perror_exit(data->infile, 1);
	}
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
}

void	setup_output_fd(t_pipex *data, int *current_pipe, int i)
{
	int	outfile_fd;

	if (i == data->cmd_num - 1)
	{
		outfile_fd = open(data->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (outfile_fd == -1)
			perror_exit(NULL, 1);
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
