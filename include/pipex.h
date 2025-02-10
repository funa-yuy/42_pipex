/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:48:53 by miyuu             #+#    #+#             */
/*   Updated: 2025/02/10 18:44:14 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <stdint.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

/* get_cmd_path */
void	free_double_pointer(char **dst);
char	*ft_getenv(const char *varname, char **envp);
char	*search_cmd_path(char *argv, char **dirs);
char	*get_cmd_path(char *argv, char **envp);

/* setup fd & pipe */
void	setup_fd(int *pipe_fd, int fd_out, int i);


void	error(char *msg);

#endif
