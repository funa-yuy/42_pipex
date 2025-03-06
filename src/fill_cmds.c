/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:06:49 by mfunakos          #+#    #+#             */
/*   Updated: 2025/03/06 13:55:14 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**parse_command(char *argv, char **envp)
{
	char	**cmd_args;
	char	*path;

	cmd_args = ft_split(argv, ' ');
	if (!cmd_args)
		return (NULL);
	path = get_cmd_path(cmd_args[0], envp);
	if (!path)
		path = cmd_args[0];
	if (path != cmd_args[0])
	{
		free(cmd_args[0]);
		cmd_args[0] = path;
	}
	return (cmd_args);
}

char	***fill_cmds(t_pipex *data, char *argv[], char **envp)
{
	char	***cmds;
	int		i;

	cmds = (char ***)malloc(sizeof(char **) * (data->cmd_num + 1));
	if (!cmds)
		perror_exit(NULL, 1);
	cmds[data->cmd_num] = NULL;
	i = 0;
	while (i < data->cmd_num)
	{
		cmds[i] = parse_command(argv[i + 2], envp);
		if (!cmds[i])
		{
			free_triple_pointer(cmds);
			perror_exit(NULL, 1);
		}
		i++;
	}
	return (cmds);
}
