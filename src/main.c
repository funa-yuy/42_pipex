/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:47:26 by miyuu             #+#    #+#             */
/*   Updated: 2025/02/14 19:49:52 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libft/libft.h"

void	execute_cmd(int input_fd, int *current_pipe, char *argv[], int i, int cmd_num)
{
	int	outfile_fd;

	if (i == 0)
	{
		input_fd = open(argv[1], O_RDWR);
		if (input_fd == -1)
			error(NULL);
	}
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);

	if (i != cmd_num - 1) {
		// 次のパイプの書き込みを標準出力に設定
		dup2(current_pipe[1], STDOUT_FILENO);
		close(current_pipe[1]);
		close(current_pipe[0]);
	}

	if (i == cmd_num - 1)
	{
		outfile_fd = open(argv[cmd_num + 2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
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

void	switch_pipefd(int **current_pipe, int	**previous_pipe, int pipe_fd1[2], int pipe_fd2[2], int i)
{
	if (i % 2 == 0)
	{
		*current_pipe = pipe_fd1;
		*previous_pipe = pipe_fd2;
	}
	else
	{
		*current_pipe = pipe_fd2;
		*previous_pipe = pipe_fd1;
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

//パイプ下準備→パイプの生成
//子プロセス作成→実行
//パイプの後処理
int	pipex(char ***cmds, char **envp, char *argv[], int cmd_num)
{
	int	pipe_fd1[2];
	int	pipe_fd2[2];
	int	input_fd;
	int	*current_pipe;
	int	*previous_pipe;
	int	i;
	pid_t	pid;
	pid_t	last_pid;
	int	infile_fd;
	int		status;
	int	last_status;

	input_fd = STDIN_FILENO;
	i = 0;
	while (i < cmd_num)
	{
		// パイプの切り替え
		switch_pipefd(&current_pipe, &previous_pipe, pipe_fd1, pipe_fd2, i);

		// 次のコマンドがある場合、パイプを作成
		if (i !=  cmd_num - 1)
			pipe(current_pipe);

		pid = fork();
		last_pid = pid;
		if (pid == 0)
		{
			execute_cmd(input_fd, current_pipe, argv, i, cmd_num);
			child_process(cmds[i], envp);
		}
		after_setup_fd(&input_fd, current_pipe, i, cmd_num);
		i++;
	}
	waitpid(last_pid, &last_status, 0);
	while (wait(&status) > 0)
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (last_status);
}

// ./pipex infile "ls -l" "wc -l" outfile
int	main(int argc, char *argv[], char **envp)
{
	char	***cmds;
	int		i;
	int		exit_status;
	int		pipe_fd[2];

	int	cmd_num;

	cmd_num = argc - 3;
	cmds = fill_cmds(cmd_num, argv, envp);
	// i = 0;
	// int	j;
	// while (i < cmd_num)
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
	exit_status = pipex(cmds, envp, argv, cmd_num);
	printf("exit_status = %d\n", exit_status);
	free_triple_pointer(cmds);

	return (exit_status);
}
