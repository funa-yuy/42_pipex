/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:38:03 by mfunakos          #+#    #+#             */
/*   Updated: 2025/03/06 13:56:07 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*search_cmd_path(char *argv, char **dirs)
{
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i] != NULL)
	{
		full_path = ft_strjoin(dirs[i], argv);
		if (!full_path)
		{
			free(argv);
			free_double_pointer(dirs);
			perror_exit(NULL, 1);
		}
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_in_path(char *argv, char **envp)
{
	char	*path;
	char	*cmd_path;
	char	**dirs;
	char	*tmp;

	path = ft_getenv("PATH", envp);
	if (!path)
		perror_exit(NULL, 1);
	dirs = ft_split(path, ':');
	if (!dirs)
		perror_exit(NULL, 1);
	free(path);
	if (!dirs)
		perror_exit(NULL, 1);
	tmp = ft_strjoin("/", argv);
	if (!tmp)
	{
		free_double_pointer(dirs);
		perror_exit(NULL, 1);
	}
	cmd_path = search_cmd_path(tmp, dirs);
	free(tmp);
	free_double_pointer(dirs);
	return (cmd_path);
}

char	*get_cmd_path(char *argv, char **envp)
{
	if (!argv || !envp)
		return (NULL);
	if (access(argv, X_OK) == 0)
		return (argv);
	return (find_in_path(argv, envp));
}
