/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 22:39:32 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/15 22:56:20 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error_cmd_not_found(char *cmd)
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
			error_cmd_not_found(cmd[0]);
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
