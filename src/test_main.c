/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:47:26 by miyuu             #+#    #+#             */
/*   Updated: 2025/02/13 16:11:01 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libft/libft.h"

// ./a.out ls　→ ○
// ./a.out "ls" → ○
// ./a.out /bin/ls → ○
// ./a.out "ls " → ×

// int	pipex(char ***cmds, char **envp, int *pipe_fd, int fd_out, int cmd_num, int	i)
// {
// 	pid_t	pid_1;
// 	int		status;
// 	int		exit_status;

// 	// fprintf(stderr, "i = %d cmd_num = %d\n", i, cmd_num);
// 	// fprintf(stderr, "最初　pipe_fd[0] = %d, pipe_fd[1] = %d, fd_out = %d\n", pipe_fd[0], pipe_fd[1], fd_out);
// 	if (i > cmd_num - 1)
// 		return (0);


// 	if (pipe(pipe_fd) < 0)
// 		error("pipe(pipe_fd)");
// 	// setup_fd(pipe_fd, fd_out, cmd_num, i);
// 	// fprintf(stderr, "次時　pipe_fd[0] = %d, pipe_fd[1] = %d, fd_out = %d\n", pipe_fd[0], pipe_fd[1], fd_out);

// 	pid_1 = fork();
// 	if (pid_1 < 0)
// 		error("pid_1 < 0");
// 		if (pid_1 == 0)
// 		{
// 			// fprintf(stderr, "最後　pipe_fd[0] = %d, pipe_fd[1] = %d, fd_out = %d\n", pipe_fd[0], pipe_fd[1], fd_out);
// 			// fprintf(stderr, "%d回目　cmd = %s\n", i, cmds[i][0]);
// 			if (i == 0)
// 			first_cmd(cmds[i], envp, pipe_fd, i);
// 			else if (i == cmd_num - 1)
// 			last_cmd(cmds[i], envp, pipe_fd, i);
// 			else
// 			middle_cmd(cmds[i], envp, pipe_fd, i);
// 			exit(0);
// 		}
// 	if (close(pipe_fd[1]) == -1)
// 		error("mian関数 close[1]");
// 	if (close(pipe_fd[0]) == -1)
// 		error("mian関数 close[0]");
// 	exit_status = pipex(cmds, envp, pipe_fd, fd_out, cmd_num, i + 1);

// 	if (i == cmd_num - 1)
// 	{
// 		fprintf(stderr, "i[%d] pid_1 = %d\n", i, pid_1);
// 		waitpid(pid_1, &status, 0);
// 		// fprintf(stderr, "i[%d]をまちました\n", i);
// 		if (WIFEXITED(status))
// 		exit_status = WEXITSTATUS(status);
// 		else if (WIFSIGNALED(status))
// 		exit_status = 128 + WTERMSIG(status);
// 	}
// 	else
// 		waitpid(pid_1, &status, 0);
// 	return (exit_status);
// }

int	main(int argc, char *argv[], char **envp)
{
	char	***cmds;
	int		i;
	int		exit_status;
	int		pipe_fd[2];
	int		fd_out;

	cmds = fill_cmds(argc, argv, envp);
	i = 0;
	// int	j;
	// while (i < argc - 1)
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

	fd_out = dup(STDOUT_FILENO);
	exit_status = 0;
	// exit_status = pipex(cmds, envp, pipe_fd, fd_out, argc - 1, 0);
	exit_status = pipex(cmds, envp, argc - 1);
	printf("exit_status = %d\n", exit_status);
	free_triple_pointer(cmds);

	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_cmd(char **cmds, char **envp, int input_fd, int	*current_pipe, int i, int cmd_num)
{
	int	outfile_fd;
	// fprintf(stderr, "i = %d  input_fd = %d\n", i,  input_fd);
	// 子プロセスで処理

	if (i == 0)
	{
		input_fd = open(IN_FILE, O_RDWR);
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
		outfile_fd = open(OUT_FILE, O_CREAT | O_RDWR, 0644);
		if (outfile_fd == -1)
			error(NULL);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
	}
	execve(cmds[0], cmds, envp);
	perror("execve failed");
	exit(1);
}

int	pipex(char ***cmds, char **envp, int cmd_num)
{
	int	pipe_fd1[2];
	int	pipe_fd2[2];
	int	input_fd;
	int	*current_pipe;
	int	*previous_pipe;
	int	i;
	pid_t pid;
	int	infile_fd;

	input_fd = STDIN_FILENO;
	i = 0;
	while (i < cmd_num)
	{

		// パイプの切り替え
		if (i % 2 == 0)
		{
			current_pipe = pipe_fd1;
			previous_pipe = pipe_fd2;
		}
		else
		{
			current_pipe = pipe_fd2;
			previous_pipe = pipe_fd1;
		}

		// 次のコマンドがある場合、パイプを作成
		if (i !=  cmd_num - 1)
			pipe(current_pipe);

		pid = fork();
		if (pid == 0)
			execute_cmd(cmds[i], envp, input_fd, current_pipe, i, cmd_num);

		if (i != 0)
			close(input_fd);  // 使い終わったパイプの読み取り側を閉じる
		if (i != cmd_num - 1)
			close(current_pipe[1]);  // パイプの書き込み側を閉じる (EOF を送る)

		input_fd = current_pipe[0];  // 次のコマンド用にパイプの読み取り側を設定
		i++;
	}
	while (wait(NULL) > 0);
	return (0);
}
