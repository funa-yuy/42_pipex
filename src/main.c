/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:47:26 by miyuu             #+#    #+#             */
/*   Updated: 2025/02/05 20:08:44 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libft/libft.h"

// ./a.out ls　→ ○
// ./a.out "ls" → ○
// ./a.out /bin/ls → ○
// ./a.out "ls " → ×

void	error(char *msg)
{
	perror(msg);
	exit(1);
}

int	pid_2_prg(int pipe_fd[2])
{
	int count;
	char c;

	printf("fork2\n");

	close(pipe_fd[1]);
	while ((count = read(pipe_fd[0], &c, 1)) > 0) {
		putchar(c);
	}
	close(pipe_fd[0]);
	return (0);
}

int	pid_1_prg(int pipe_fd[2])
{
	printf("fork1\n");

	char *p = "Hello, my kid.";
	close(pipe_fd[0]);
	while (*p != '\0') {
		if (write(pipe_fd[1], p, 1) < 0) {
				perror("write");
				exit(1);
		}
		p++;
	}
	close(pipe_fd[1]);
	return (0);
}

void	pipex(int argc, char *argv[], char **envp)
{
	pid_t	pid_1;
	pid_t	pid_2;
	int	status;
	int		pipe_fd[2];


	if (pipe(pipe_fd) < 0)
		error("pipe(pipe_fd)");
	pid_1 = fork();
	if (pid_1 < 0)
		error("pid_1 < 0");
	else if (pid_1 == 0)
		exit(pid_1_prg(pipe_fd));

	pid_2 = fork();
	if (pid_2 < 0)
		error("pid_2 < 0");
	else if (pid_2 == 0)
		exit(pid_2_prg(pipe_fd));


	printf("fork1の親です\n");
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_1, &status, 0);
	waitpid(pid_2, &status, 0);
}


int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	char	**pargv;
	char	**cargv;
	char	**cmd;
	char	**cmd_2;
	char	*cmd_path;
	int		i;

	// printf("argv[1] = %s\n", argv[1]);
	// cmd_path = get_cmd_path(argv[1], envp);
	// if (!cmd_path)
	// 	error("not found");
	// printf("cmd_path = %s\n", cmd_path);
	// free(cmd_path);

	// if (argc != 5)
	// 	return (0);

	pipex(argc, argv, envp);


/*
	pipe
	fork
	親
		wait(&status)
	子
		char	**ag;
		ag = split(argv[1]);
		cmd_path = get_cmd_path(ag[0], envp);
		execve(cmd_path, pargv, envp);
		pipeで
		//エラー
			free()
	wait(&status);
	子
		char	**ag;
		ag = split(argv[argc - 1]);
		cmd_path = get_cmd_path(ag[0], envp);
		execve(cmd_path, pargv, envp);
		//エラー
			free()
	wait(&status);
*/

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
