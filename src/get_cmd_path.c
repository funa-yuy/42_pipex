/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:38:03 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/18 17:08:57 by miyuu            ###   ########.fr       */
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
			error("full_path");
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
		error("not found ft_getenv");
	dirs = ft_split(path, ':');
	if (!dirs)
		error("split");
	free(path);
	if (!dirs)
		error("dirs");
	tmp = ft_strjoin("/", argv);
	if (!tmp)
	{
		free_double_pointer(dirs);
		error("full_path");
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

// char	*get_cmd_path(char *argv, char **envp)
// {
// 	char	*path;
// 	char	*cmd_path;
// 	char	**dirs;
// 	char	*tmp;

// 	if (!argv || !envp)
// 		return (NULL);
// 	if (access(argv, X_OK) == 0)
// 		return (argv);
// 	path = ft_getenv("PATH", envp);
// 	if (!path)
// 		error("not found ft_getenv");
// 	dirs = ft_split(path, ':');
// 	if (!dirs)
// 		error("split");
// 	free(path);
// 	if (!dirs)
// 		error("dirs");
// 	tmp = ft_strjoin("/", argv);
// 	if (!tmp)
// 	{
// 		free_double_pointer(dirs);
// 		error("full_path");
// 	}
// 	cmd_path = search_cmd_path(tmp, dirs);
// 	free(tmp);
// 	free_double_pointer(dirs);
// 	return (cmd_path);
// }
