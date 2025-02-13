/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:13:06 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/12 18:10:55 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	last_cmd(char **cmd, char **envp, int *pipe_fd, int i)
{
	//pipe_fd[1]は使わないのでclose
	if (close(pipe_fd[1]) == -1)
		error("close[1]");
	//


	//pipe_fd[0]をSTDIN_FILENOにする
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		error("dup");
	if (close(pipe_fd[0]) == -1)
		error("close[0]");
	//

	// fprintf(stderr, "last_cmd関数:fork[%d]の子供です。実行コマンドは→%s\n", i, cmd[0]);
	execve(cmd[0], cmd, envp);
	error("last_cmd");
}

void	first_cmd(char **cmd, char **envp, int *pipe_fd, int i)
{
	//pipe_fd[0]は使わないのでclose
	if (close(pipe_fd[0]) == -1)
		error("close[0]");
	//


	//pipe_fd[1]をSTDOUT_FILENOにする
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error("dup");
	if (close(pipe_fd[1]) == -1)
		error("close[1]");
	//


	// fprintf(stderr, "first_cmd関数:fork[%d]の子供です。実行コマンドは→%s\n", i, cmd[0]);
	execve(cmd[0], cmd, envp);
	error("first_cmd");
}

void	middle_cmd(char **cmd, char **envp, int *pipe_fd, int i)
{

	//pipe_fd[0]をSTDIN_FILENOにする
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		error("dup");
	if (close(pipe_fd[0]) == -1)
		error("close[0]");
	//

	//pipe_fd[1]をSTDOUT_FILENOにする
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error("dup");
	if (close(pipe_fd[1]) == -1)
		error("close[1]");
	//


	if (close(pipe_fd[0]) == -1)
		error("close[0]");
	// fprintf(stderr, "middle_cmd関数:fork[%d]の子供です。実行コマンドは→%s\n", i, cmd[0]);
	execve(cmd[0], cmd, envp);
	error("middle_cmd");
}
