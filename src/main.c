/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:47:26 by miyuu             #+#    #+#             */
/*   Updated: 2025/02/10 22:39:53 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libft/libft.h"

// ./a.out ls　→ ○
// ./a.out "ls" → ○
// ./a.out /bin/ls → ○
// ./a.out "ls " → ×

int	pipex(char ***cmds, char **envp, int *pipe_fd, int fd_out, int cmd_num, int	i)
{
	pid_t	pid_1;
	int		status;
	int		exit_status;

	fprintf(stderr, "i = %d\n", i);
	fprintf(stderr, "最初　pipe_fd[0] = %d, pipe_fd[1] = %d, fd_out = %d\n", pipe_fd[0], pipe_fd[1], fd_out);
	if (i > cmd_num)
		return (0);

	setup_fd(pipe_fd, fd_out, cmd_num, i);
	fprintf(stderr, "次時　pipe_fd[0] = %d, pipe_fd[1] = %d, fd_out = %d\n", pipe_fd[0], pipe_fd[1], fd_out);

	pid_1 = fork();
	if (pid_1 < 0)
		error("pid_1 < 0");
	if (pid_1 == 0)
	{
		fprintf(stderr, "最後　pipe_fd[0] = %d, pipe_fd[1] = %d, fd_out = %d\n", pipe_fd[0], pipe_fd[1], fd_out);
		fprintf(stderr, "%d回目　cmd = %s\n", i, cmds[i][0]);
		if (i == 0)
			first_cmd(cmds[i], envp, i);
		if (i == cmd_num - 1)
			last_cmd(cmds[i], envp, i);
		else
			middle_cmd(cmds[i], envp, i);
		exit(0);
	}
	status = pipex(cmds, envp, pipe_fd, fd_out, cmd_num, i + 1);
	if (i == cmd_num - 1)
	{
		fprintf(stderr, "i[%d] pid_1 = %d\n", i, pid_1);
		waitpid(pid_1, &status, 0);
		fprintf(stderr, "i[%d]をまちました\n", i);
		exit_status = status;
	}
	else
	{
		fprintf(stderr, "i[%d] pid_1 = %d\n", i, pid_1);
		waitpid(pid_1, &status, 0);
		fprintf(stderr, "i[%d]をまちました\n", i);
	}
	return (exit_status);
}

int	main(int argc, char *argv[], char **envp)
{
	char	***cmds;
	int		i;
	int		pipe_fd[2];
	int		fd_out;

	cmds = fill_cmds(argc, argv, envp);
	i = 0;
	while (i < argc - 1)
	{
		printf("cmds[%d]= ", i);
		int	j = 0;
		while (cmds[i][j] != NULL)
		{
			printf("\"%s\" ",cmds[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

	fd_out = dup(STDOUT_FILENO);
	i = pipex(cmds, envp, pipe_fd, fd_out, argc - 1, 0);
	printf("pipexのreturn = %d\n", i);
	free_triple_pointer(cmds);

	return (0);
}

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

// int	main(int argc, char *argv[], char **envp)
// {
// 	(void)argc;
// 	char	**pargv;
// 	char	**cargv;
// 	char	**cmd;
// 	char	**cmd_2;
// 	char	*cmd_path;
// 	int		i;
// 	int		filedes[2];


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
	// 	free(c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md_2);
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
// 	return (0);
// }
