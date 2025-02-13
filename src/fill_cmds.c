/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:06:49 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/13 16:57:13 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	***fill_cmds(int argc, char *argv[], char **envp)
{
	char	***cmds;
	char	*tmp;
	int		i;

	cmds = (char ***)malloc(sizeof(char **) * argc);
	if (!cmds)
		error("malloc");
	cmds[argc -1] = NULL;
	i = 0;
	while (i < argc - 1)
	{
		cmds[i] = ft_split(argv[i + 1], ' ');
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
