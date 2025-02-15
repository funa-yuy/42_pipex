/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:48:53 by miyuu             #+#    #+#             */
/*   Updated: 2025/02/15 22:16:02 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* header file*/
# include "../libft/libft.h"

/* library */
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <stdint.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdbool.h>

#include <errno.h>//使っていいかは謎 errno

/* define */
# define OUT_FILE	"./outfile"
# define IN_FILE	"./infile"

typedef struct		s_fd
{
	int		input_fd;
	int		pipe_fd1[2];
	int		pipe_fd2[2];
	int		*current_pipe;
	int		*previous_pipe;
}			t_fd;


typedef struct		s_pipex
{
	int		cmd_num;
	char	***cmds;
	char	*infile;
	char	*outfile;
}			t_pipex;

/* pipex */
// int	pipex(char ***cmds, char **envp, char *argv[], int cmd_num);
int	pipex(t_pipex data, char ***cmds, char **envp);

/* child_process */
// void	child_process(t_pipex data, int input_fd, int *current_pipe, int i);
void	child_process(t_fd *fd_data, t_pipex data, char **cmd, char **envp, int i);
void	execute_cmd(char **cmds, char **envp);

/* fill cmds */
// char	***fill_cmds(int argc, char *argv[], char **envp);
char	***fill_cmds(t_pipex data, char *argv[], char **envp);

/* get_cmd_path */
char	*ft_getenv(const char *varname, char **envp);
char	*search_cmd_path(char *argv, char **dirs);
char	*get_cmd_path(char *argv, char **envp);

/* setup fd & pipe */
void	switch_pipefd(t_fd *fd_data, int i);
// void	after_setup_fd(int *input_fd, int *current_pipe, int i, int cmd_num);
void	after_setup_fd(t_fd *fd_data, int i, int cmd_num);


/* utils */
void	free_double_pointer(char **str);
void	free_triple_pointer(char ***str);
void	error(char *msg);

#endif
