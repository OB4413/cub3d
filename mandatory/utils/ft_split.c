/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:33:43 by ynadime           #+#    #+#             */
/*   Updated: 2025/08/26 11:22:38 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

static size_t	word_len(char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s != c && *s)
	{
		count++;
		s++;
	}
	return (count);
}

static int	fill(char **dst, char *s, char c, size_t words)
{
	size_t	i;
	size_t	wordlen;

	i = 0;
	while (i < words)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			wordlen = word_len(s, c);
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

static size_t	wordcount(char *s, char c)
{
	size_t	f;
	size_t	count;

	f = 1;
	count = 0;
	while (*s)
	{
		if (*s != c && f == 1)
		{
			f = 0;
			count++;
		}
		else if (*s == c && f == 0)
			f = 1;
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	count;

	if (!s)
		return (NULL);
	count = wordcount((char *)s, c);
	str = (char **)ft_malloc((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	if (fill(str, (char *)s, c, count))
		return (NULL);
	return (str);
}
