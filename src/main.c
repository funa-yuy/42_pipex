/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:47:26 by miyuu             #+#    #+#             */
/*   Updated: 2025/02/02 17:39:52 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include "pipex.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// ./a.out ./ "ls -l -a" "wc -l"

void	error(char *msg)
{
	perror(msg);
	exit(1);
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
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*search_cmd_path(char *argv, char **envp)
{
	char	*path;
	char	*full_path;
	int		i;
	char	**cmd;

	path = ft_getenv("PATH", envp);
	if (!path)
		error("not found ft_getenv");
	i = 0;
	cmd = ft_split(path, ':');
	if (!cmd)
	{
		free(path);
		error("cmd");
	}
	free(path);
	while (cmd[i] != NULL)
	{
		full_path = ft_strjoin(cmd[i], ft_strjoin("/", argv));
		if (!full_path)
		{
			free(cmd);
			error("full_path");
		}
		if (access(full_path, X_OK) == 0)
		{
			free(cmd);
			return (full_path);
		}
		i++;
	}
	free(cmd);
	return (NULL);
}

//絶対パスで来たとき、相対パスで来たとき
int	main(int argc, char *argv[], char **envp)
{
	int		filedes[2];
	char	**pargv;
	char	**cargv;
	pid_t	pid;
	char	**cmd;
	char	**cmd_2;
	char	*cmd_path;
	int		i;

	cmd_path = search_cmd_path(argv[1], envp);
	if (!cmd_path)
		error("not found");
	printf("cmd_path = %s\n", cmd_path);
	// if (argc != 5)
	// 	return (0);

	// if (pipe(filedes) < 0)
	// 	error("pipe(filedes)");
	// pid = fork();
	// if (pid < 0)
	// 	error("pid < 0");

	// if (pid > 0)
	// {
	// 	if (close(filedes[1]) == -1)
	// 		error("lose(filedes[1])");
	// 	wait(NULL);
	// 	close(0);
	// 	if (dup2(filedes[0], 0) < 0)
	// 		exit(1);
	// 	close(filedes[0]);

	// 	cmd_2 = ft_split(argv[3], ' ');
	// 	i = 0;
	// 	while (cmd_2[i] != NULL)
	// 		i++;
	// 	pargv = malloc(i + 2 * sizeof(char *));
	// 	i = 0;
	// 	while (cmd_2[i] != NULL)
	// 	{
	// 		pargv[i] = cmd_2[i];
	// 		printf("%s \n", cmd_2[i]);
	// 		i++;
	// 	}
	// 	pargv[i] = NULL;
	// 	// pargv[0] = "wc";
	// 	// pargv[1] = "-l";
	// 	// pargv[2] = NULL;
	// 	execve("/usr/bin/wc", pargv, envp);
	// 	free(cmd_2);
	// 	free(pargv);
	// 	error("wc failed");
	// }
	// else if (pid == 0)
	// {
	// 	if (close(filedes[0]) == -1)
	// 		error("close(filedes[0])");
	// 	close(1);
	// 	if (dup2(filedes[1], 1) < 0)
	// 		exit(1);
	// 	close(filedes[1]);
	// 	cmd = ft_split(argv[2], ' ');
	// 	i = 0;
	// 	while (cmd[i] != NULL)
	// 		i++;
	// 	cargv = malloc(i + 2 * sizeof(char *));
	// 	i = 0;
	// 	while (cmd[i] != NULL)
	// 	{
	// 		cargv[i] = cmd[i];
	// 		printf("%s \n", cmd[i]);
	// 		i++;
	// 	}
	// 	cargv[i] = argv[1];
	// 	cargv[i + 1] = NULL;
	// 	execve("/bin/ls", cargv, envp);
	// 	free(cmd);
	// 	free(cargv);
	// 	error("ls failed");
	// }
	return (0);
}
