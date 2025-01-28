/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:50:55 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/28 18:16:44 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

//ls

int	main(void)
{
	extern char	**environ;
	char		*exargv[3];

	exargv[0] = "ls";
	exargv[1] = "-l";
	exargv[2] = NULL;
	execve("/bin/ls", exargv, environ);
	return (0);
}
