/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:47:26 by miyuu             #+#    #+#             */
/*   Updated: 2025/02/16 02:13:24 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libft/libft.h"

int	wait_status(pid_t last_pid)
{
	int	status;
	int	last_status;

	waitpid(last_pid, &last_status, 0);
	while (wait(&status) > 0)
		;
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (last_status);
}

int	pipex(t_pipex *data, char **envp)
{
	t_fd	fd_data;
	int		input_fd;
	int		i;
	pid_t	pid;

	fd_data.input_fd = STDIN_FILENO;
	i = 0;
	while (i < data->cmd_num)
	{
		switch_pipefd(&fd_data, i);
		if (i != data->cmd_num - 1)
			pipe(fd_data.current_pipe);
		pid = fork();
		if (pid == 0)
			child_process(&fd_data, data, envp, i);
		after_exec_setup_fd(&fd_data, i, data->cmd_num);
		i++;
	}
	return (wait_status(pid));
}

void	data_init(t_pipex *data, int argc, char *argv[], char **envp)
{
	data->cmd_num = argc - 3;
	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	data->cmds = fill_cmds(data, argv, envp);
}

int	main(int argc, char *argv[], char **envp)
{
	int		exit_status;
	t_pipex	data;

	data_init(&data, argc, argv, envp);
	exit_status = 0;
	exit_status = pipex(&data, envp);
	free_triple_pointer(data.cmds);
	return (exit_status);
}

	// int		i;
	// i = 0;
	// int	j;
	// while (i < data.cmd_num)
	// {
	// 	printf("cmds[%d]= ", i);
	// 	j = 0;
	// 	while (data.cmds[i][j] != NULL)
	// 	{
	// 		printf("\"%s\" ",data.cmds[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
