/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:47:26 by miyuu             #+#    #+#             */
/*   Updated: 2025/02/15 16:16:25 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libft/libft.h"

void	execute_cmd(t_pipex data, int input_fd, int *current_pipe, int i)
{
	int	outfile_fd;

	if (i == 0)
	{
		input_fd = open(data.infile, O_RDWR);
		if (input_fd == -1)
			error(NULL);
	}
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);

	if (i != data.cmd_num - 1) {
		// 次のパイプの書き込みを標準出力に設定
		dup2(current_pipe[1], STDOUT_FILENO);
		close(current_pipe[1]);
		close(current_pipe[0]);
	}

	if (i == data.cmd_num - 1)
	{
		outfile_fd = open(data.outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (outfile_fd == -1)
			error(NULL);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
	}
}

void	child_process(char **cmds, char **envp)
{
	execve(cmds[0], cmds, envp);
	perror("execve failed");
	exit(126);
}

void	switch_pipefd(t_fd *fd_data, int **current_pipe, int **previous_pipe, int i)
{
	if (i % 2 == 0)
	{
		fd_data->current_pipe = fd_data->pipe_fd1;
		fd_data->previous_pipe = fd_data->pipe_fd2;
	}
	else
	{
		fd_data->current_pipe = fd_data->pipe_fd2;
		fd_data->previous_pipe = fd_data->pipe_fd1;
	}
}

void	after_setup_fd(int *input_fd, int *current_pipe, int i, int cmd_num)
{
	if (i != 0)
		close(*input_fd);  // 使い終わったパイプの読み取り側を閉じる
	if (i != cmd_num - 1)
		close(current_pipe[1]);  // パイプの書き込み側を閉じる (EOF を送る)

	*input_fd = current_pipe[0];  // 次のコマンド用にパイプの読み取り側を設定
}

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

//パイプ下準備→パイプの生成
//子プロセス作成→実行
//パイプの後処理
int	pipex(t_pipex data, char ***cmds, char **envp)
{
	t_fd	fd_data;
	// int	pipe_fd1[2];
	// int	pipe_fd2[2];
	int	input_fd;
	int	*current_pipe;
	int	*previous_pipe;
	int	i;
	pid_t	pid;
	pid_t	last_pid;

	input_fd = STDIN_FILENO;
	i = 0;
	while (i < data.cmd_num)
	{
		// パイプの切り替え
		switch_pipefd(&fd_data, &current_pipe, &previous_pipe, i);

		if (i !=  data.cmd_num - 1)
			pipe(fd_data.current_pipe);

		pid = fork();
		last_pid = pid;
		if (pid == 0)
		{
			execute_cmd(data, input_fd, fd_data.current_pipe, i);
			child_process(cmds[i], envp);
		}
		after_setup_fd(&input_fd, fd_data.current_pipe, i, data.cmd_num);
		i++;
	}
	return (wait_status(last_pid));
}

int	main(int argc, char *argv[], char **envp)
{
	char	***cmds;
	int		i;
	int		exit_status;
	t_pipex	data;

	int	cmd_num;
	data.cmd_num = argc - 3;
	data.infile = argv[1];
	data.outfile = argv[argc - 1];
	cmd_num = argc - 3;
	cmds = fill_cmds(data, argv, envp);
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
	// printf("infile = %s\n", data.infile);
	// printf("outfile =%s\n", data.outfile);
	exit_status = 0;
	exit_status = pipex(data, cmds, envp);
	// printf("exit_status = %d\n", exit_status);
	free_triple_pointer(cmds);

	return (exit_status);
}
