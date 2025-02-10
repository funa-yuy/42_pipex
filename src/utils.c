/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:39:41 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/10 21:48:56 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error(char *msg)
{
	perror("ERROR");
	perror(msg);
	exit(1);
}

void	free_double_pointer(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_triple_pointer(char ***str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free_double_pointer(str[i]);
		i++;
	}
	free(str);
}
