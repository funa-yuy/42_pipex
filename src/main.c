/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:47:26 by miyuu             #+#    #+#             */
/*   Updated: 2025/02/15 22:14:22 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libft/libft.h"

int	wait_status(pid_t last_pid)
{
	int	status;
	int	last_status;

	waitpid(last_pid, &last_status, 0);
	while (wait(&status) > 0);
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (last_status);
}

int	pipex(t_pipex data, char ***cmds, char **envp)
{
	t_fd	fd_data;
	int		input_fd;
	int		i;
	pid_t	pid;

	fd_data.input_fd = STDIN_FILENO;
	i = 0;
	while (i < data.cmd_num)
	{
		switch_pipefd(&fd_data, i);

		if (i != data.cmd_num - 1)
			pipe(fd_data.current_pipe);

		pid = fork();
		if (pid == 0)
		{
			child_process(&fd_data, data, cmds[i], envp, i);
			// child_process(data, cmds[i], envp, input_fd, fd_data.current_pipe, i);
			// execute_cmd(cmds[i], envp);
		}
		// after_setup_fd(&input_fd, fd_data.current_pipe, i, data.cmd_num);
		after_setup_fd(&fd_data, i, data.cmd_num);
		i++;
	}
	return (wait_status(pid));
}

void	data_init(t_pipex *data, int argc, char *argv[])
{
	data->cmd_num = argc - 3;
	data->infile = argv[1];
	data->outfile = argv[argc - 1];
}

int	main(int argc, char *argv[], char **envp)
{
	char	***cmds;
	int		exit_status;
	t_pipex	data;

	data_init(&data, argc, argv);
	cmds = fill_cmds(data, argv, envp);
	// int		i;
	// i = 0;
	// int	j;
	// while (i < data.cmd_num)
	// {
	// 	printf("cmds[%d]= ", i);
	// 	j = 0;
	// 	while (cmds[i][j] != NULL)
	// 	{
	// 		printf("\"%s\" ",cmds[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }

	exit_status = 0;
	exit_status = pipex(data, cmds, envp);
	// printf("exit_status = %d\n", exit_status);
	free_triple_pointer(cmds);

	return (exit_status);
}
