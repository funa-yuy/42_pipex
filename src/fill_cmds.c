/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:06:49 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/14 20:50:16 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	***fill_cmds(t_pipex data, char *argv[], char **envp)
{
	char	***cmds;
	char	*tmp;
	int		i;

	cmds = (char ***)malloc(sizeof(char **) * (data.cmd_num + 1));
	if (!cmds)
		error("malloc");
	cmds[data.cmd_num] = NULL;
	i = 0;
	while (i < data.cmd_num)
	{
		cmds[i] = ft_split(argv[i + 2], ' ');
		if (!cmds)
		{
			free_triple_pointer(cmds);
			error("ft_split");
		}
		tmp = NULL;
		tmp = get_cmd_path(cmds[i][0], envp);
		if (!tmp)
		{
			free_triple_pointer(cmds);
			error("get_cmd_path");
		}
		if (tmp != cmds[i][0])
		{
			free(cmds[i][0]);
			cmds[i][0] = tmp;
		}
		i++;
	}
	return (cmds);
}
