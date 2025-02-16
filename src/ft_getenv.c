/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 22:49:57 by miyuu             #+#    #+#             */
/*   Updated: 2025/02/16 22:53:39 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// char	*ft_getenv(const char *varname, char **envp)
// {
// 	char	*path;
// 	char	*tmp;
// 	int		i;
// 	int		v_len;

// 	i = 0;
// 	if (!varname || !envp)
// 		return (NULL);
// 	v_len = ft_strlen(varname);
// 	tmp = NULL;
// 	if (varname[v_len - 1] != '=')
// 	{
// 		tmp = ft_strjoin(varname, "=");
// 		if (!tmp)
// 			error("ft_strjoin");
// 		varname = tmp;
// 		v_len++;
// 	}
// 	while (envp[i] != NULL)
// 	{
// 		if (ft_strncmp(envp[i], varname, v_len) == 0)
// 		{
// 			path = ft_substr(envp[i], v_len, ft_strlen(envp[i]) - v_len);
// 			if (!path)
// 				error("ft_substr");
// 			if (tmp)
// 				free(tmp);
// 			return (path);
// 		}
// 		i++;
// 	}
// 	if (tmp)
// 		free(tmp);
// 	return (NULL);
// }

char	*prepare_varname(char *varname)
{
	char	*tmp;
	int		v_len;

	if (!varname)
		return (NULL);
	v_len = ft_strlen(varname);
	tmp = NULL;
	if (varname[v_len - 1] != '=')
	{
		tmp = ft_strjoin(varname, "=");
		if (!tmp)
			error("ft_strjoin");
		return (tmp);
	}
	return (ft_strdup(varname));
}

char	*find_env_value(char *varname, char **envp)
{
	char	*path;
	int		i;
	int		v_len;

	if (!varname || !envp)
		return (NULL);
	v_len = ft_strlen(varname);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], varname, v_len) == 0)
		{
			path = ft_substr(envp[i], v_len, ft_strlen(envp[i]) - v_len);
			if (!path)
				error("ft_substr");
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*ft_getenv(char *varname, char **envp)
{
	char	*path;
	char	*v_name;

	if (!varname || !envp)
		return (NULL);
	v_name = prepare_varname(varname);
	if (!v_name)
		return (NULL);
	path = find_env_value(v_name, envp);
	free(v_name);
	return (path);
}
