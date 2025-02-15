/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:13:06 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/15 22:42:30 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(t_fd *fd_data, t_pipex data, char **cmd, char **envp, int i)
{
	int	outfile_fd;

	setup_input_fd(data, fd_data->input_fd, fd_data->current_pipe, i);
	setup_output_fd(data, fd_data->current_pipe, i);
	execute_cmd(cmd, envp);
}
