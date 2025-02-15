/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:43:21 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/15 18:12:58 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	switch_pipefd(t_fd *fd_data, int i)
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
