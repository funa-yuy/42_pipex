/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:43:21 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/12 13:16:34 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	setup_fd(int *pipe_fd, int fd_out, int cmd_num, int i)
{
	int	fd;

	if (i != 0)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
			error("dup");
		if (close(pipe_fd[0]) == -1)
			error("close[0]");
	}
	if (i == cmd_num - 1)
	{
		fd = open(OUT_FILE, O_CREAT | O_RDWR, 0644);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			error("dup");

	}
	else
	{
		if (pipe(pipe_fd) < 0)
			error("pipe(pipe_fd)");
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			error("dup");
		if (close(pipe_fd[1]) == -1)
			error("close[1]");
	}
}
