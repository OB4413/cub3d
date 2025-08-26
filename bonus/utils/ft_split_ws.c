/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:44:38 by ynadime           #+#    #+#             */
/*   Updated: 2025/08/25 20:11:26 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

static void	free_array(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		ft_free(s[i]);
		i++;
	}
	ft_free(s);
}

static size_t	word_len(char *s)
{
	size_t	count;

	count = 0;
	while (!ft_isspace(*s) && *s)
	{
		count++;
		s++;
	}
	return (count);
}

static int	fill(char **dst, char *s, size_t words)
{
	size_t	i;
	size_t	wordlen;

	i = 0;
	while (i < words)
	{
		while (ft_isspace(*s) && *s)
			s++;
		if (!ft_isspace(*s) && *s)
		{
			wordlen = word_len(s);
			dst[i] = (char *)ft_malloc(sizeof(char) * (wordlen + 1));
			if (!dst[i])
			{
				free_array(dst);
				return (1);
			}
			ft_strlcpy(dst[i], s, (wordlen + 1));
			s += wordlen;
		}
		i++;
	}
	dst[i] = NULL;
	return (0);
}

static size_t	wordcount(char *s)
{
	size_t	f;
	size_t	count;

	f = 1;
	count = 0;
	while (*s)
	{
		if (!ft_isspace(*s) && f == 1)
		{
			f = 0;
			count++;
		}
		else if (ft_isspace(*s) && f == 0)
			f = 1;
		s++;
	}
	return (count);
}

char	**ft_split_ws(char const *s)
{
	char	**str;
	size_t	count;

	if (!s)
		return (NULL);
	count = wordcount((char *)s);
	str = (char **)ft_malloc((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	if (fill(str, (char *)s, count))
		return (NULL);
	return (str);
}
