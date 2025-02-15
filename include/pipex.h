/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:48:53 by miyuu             #+#    #+#             */
/*   Updated: 2025/02/15 16:05:29 by mfunakos         ###   ########.fr       */
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

/* define */
# define OUT_FILE	"./outfile"
# define IN_FILE	"./infile"

typedef struct		s_fd
{
	int		input_fd;
	int		pipe_fd1[2];
	int		pipe_fd2[2];
	// int		*current_pipe;
	// int		*previous_pipe;
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
void	first_cmd(char **cmd, char **envp, int *pipe_fd, int i);
void	middle_cmd(char **cmd, char **envp, int *pipe_fd, int i);
void	last_cmd(char **cmd, char **envp, int *pipe_fd, int i);

/* fill cmds */
// char	***fill_cmds(int argc, char *argv[], char **envp);
char	***fill_cmds(t_pipex data, char *argv[], char **envp);

/* get_cmd_path */
char	*ft_getenv(const char *varname, char **envp);
char	*search_cmd_path(char *argv, char **dirs);
char	*get_cmd_path(char *argv, char **envp);

/* setup fd & pipe */
// void	switch_pipefd(int	**current_pipe, int	**previous_pipe, int	pipe_fd1[2], int pipe_fd2[2], int i);
// void	switch_pipefd(t_fd fd_data, int **current_pipe, int **previous_pipe, int pipe_fd1[2], int pipe_fd2[2], int i);


/* utils */
void	free_double_pointer(char **str);
void	free_triple_pointer(char ***str);
void	error(char *msg);

#endif
