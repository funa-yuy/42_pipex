/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:13:06 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/16 01:56:06 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(t_fd *fd_data, t_pipex *data, char **envp, int i)
{
	int	outfile_fd;

	setup_input_fd(data, fd_data->input_fd, fd_data->current_pipe, i);
	setup_output_fd(data, fd_data->current_pipe, i);
	execute_cmd(data->cmds[i], envp);
}
