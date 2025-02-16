/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:39:32 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/16 20:56:18 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	command_not_found_handle(char *cmd)
{
	char	*error_msg;

	error_msg = ": command not found\n";
	write(2, cmd, ft_strlen(cmd));
	write(2, error_msg, ft_strlen(error_msg));
}

void	execute_cmd(char **cmd, char **envp)
{
	if (access(cmd[0], F_OK) == -1)
	{
		if (ft_strchr (cmd[0], '/') == NULL)
			command_not_found_handle(cmd[0]);
		else
			perror(cmd[0]);
		exit(127);
	}
	if (execve(cmd[0], cmd, envp) < 0)
	{
		perror(cmd[0]);
		exit(126);
	}
}
