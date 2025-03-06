/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:39:41 by mfunakos          #+#    #+#             */
/*   Updated: 2025/03/06 14:16:49 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	perror_exit(char *msg, int status)
{
	perror(msg);
	exit(status);
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
