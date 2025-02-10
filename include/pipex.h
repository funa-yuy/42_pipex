/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:48:53 by miyuu             #+#    #+#             */
/*   Updated: 2025/02/10 22:41:50 by mfunakos         ###   ########.fr       */
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
# define IN_FILE	"infile"

/* pipex */
int		pipex(char ***cmds, char **envp, int *pipe_fd, int fd_out, int cmd_num, int	i);

/* child_process */
void	first_cmd(char **cmd, char **envp, int i);
void	middle_cmd(char **cmd, char **envp, int i);
void	last_cmd(char **cmd, char **envp, int i);

/* fill cmds */
char	***fill_cmds(int argc, char *argv[], char **envp);

/* get_cmd_path */
char	*ft_getenv(const char *varname, char **envp);
char	*search_cmd_path(char *argv, char **dirs);
char	*get_cmd_path(char *argv, char **envp);

/* setup fd & pipe */
void	setup_fd(int *pipe_fd, int fd_out, int cmd_num, int i);

/* utils */
void	free_double_pointer(char **str);
void	free_triple_pointer(char ***str);
void	error(char *msg);

#endif
