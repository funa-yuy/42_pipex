/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:06:49 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/10 21:07:55 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	***fill_cmds(int argc, char *argv[], char **envp)
{
	char	***cmds;
	char	*tmp;
	int		i;

	cmds = (char ***)malloc(sizeof(char **) * (argc - 1));
	if (!cmds)
		error("malloc");
	i = 0;
	while (i < argc - 1)
	{
		cmds[i] = ft_split(argv[i + 1], ' ');
		if (!cmds)
			error("split");
		tmp = NULL;
		tmp = get_cmd_path(cmds[i][0], envp);
		if (!tmp)
			error("get_cmd_path");
		free(cmds[i][0]);
		cmds[i][0] = tmp;
		i++;
	}
	return (cmds);
}
