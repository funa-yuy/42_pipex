/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:47:26 by miyuu             #+#    #+#             */
/*   Updated: 2025/02/13 17:34:02 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libft/libft.h"
#include <sys/types.h>

// ./a.out ls　→ ○
// ./a.out "ls" → ○
// ./a.out /bin/ls → ○
// ./a.out "ls " → ×


void execute_cmd(char **cmds, char **envp, int input_fd, int *current_pipe, char *argv[], int i, int cmd_num)
{
	int	outfile_fd;
	// fprintf(stderr, "i = %d  cmds[0] = %s\n", i, cmds[0]);
	// 子プロセスで処理

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
	execve(cmds[0], cmds, envp);
	perror("execve failed");
	exit(1);
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
			execute_cmd(cmds[i], envp, input_fd, current_pipe, argv, i, cmd_num);

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

	return (0);
}
