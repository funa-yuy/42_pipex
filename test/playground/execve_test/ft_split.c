/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:17:27 by mfunakos          #+#    #+#             */
/*   Updated: 2025/02/01 20:47:58 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static unsigned int	ft_substr_count(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c
			&& (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len);

static unsigned int	ft_substr_len(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_free(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		count;
	int		i;

	count = 0;
	i = 0;
	dst = malloc((ft_substr_count(s, c) + 1) * sizeof(char *));
	if (!dst || !s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			dst[count] = ft_substr(s, i, ft_substr_len(&s[i], c));
			if (!dst[count])
				return (ft_free(dst, count));
			count++;
			i += ft_substr_len(&s[i], c);
		}
		else
			i++;
	}
	dst[count] = 0;
	return (dst);
}
