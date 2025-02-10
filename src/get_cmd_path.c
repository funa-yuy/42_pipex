/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:38:03 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/10 20:19:39 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_double_pointer(char **dst)
{
	int	i;

	i = 0;
	while (dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
}

char	*ft_getenv(const char *varname, char **envp)
{
	char	*path;
	char	*tmp;
	int		i;
	int		v_len;

	i = 0;
	if (!varname || !envp)
		return (NULL);
	v_len = ft_strlen(varname);
	tmp = NULL;
	if (varname[v_len - 1] != '=')
	{
		tmp = ft_strjoin(varname, "=");
		if (!tmp)
			error("ft_strjoin");
		varname = tmp;
		v_len++;
	}
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], varname, v_len) == 0)
		{
			path = ft_substr(envp[i], v_len, ft_strlen(envp[i]) - v_len);
			if (!path)
				error("ft_substr");
			if (tmp)
				free(tmp);
			return (path);
		}
		i++;
	}
	if (tmp)
		free(tmp);
	return (NULL);
}

char	*search_cmd_path(char *argv, char **dirs)
{
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i] != NULL)
	{
		// full_path = ft_strjoin(dirs[i], ft_strjoin("/", argv));
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

char	*get_cmd_path(char *argv, char **envp)
{
	char	*path;
	char	*cmd_path;
	char	**dirs;
	char	*tmp;

	if (!argv || !envp)
		return (NULL);
	if (access(argv, X_OK) == 0)
		return (argv);
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
