/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_setup_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:43:21 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/15 22:38:13 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	switch_pipefd(t_fd *fd_data, int i)
{
	if (i % 2 == 0)
	{
		fd_data->current_pipe = fd_data->pipe_fd1;
		fd_data->previous_pipe = fd_data->pipe_fd2;
	}
	else
	{
		fd_data->current_pipe = fd_data->pipe_fd2;
		fd_data->previous_pipe = fd_data->pipe_fd1;
	}
}

void	after_exec_setup_fd(t_fd *fd_data, int i, int cmd_num)
{
	if (i != 0)
		close(fd_data->input_fd);
	if (i != cmd_num - 1)
		close(fd_data->current_pipe[1]);
	fd_data->input_fd = fd_data->current_pipe[0];
}
