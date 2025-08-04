/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:33:43 by ynadime           #+#    #+#             */
/*   Updated: 2024/10/29 11:33:44 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

static void	ft_free(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
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
			dst[i] = (char *)malloc(sizeof(char) * (wordlen + 1));
			if (!dst[i])
			{
				ft_free(dst);
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
	str = (char **)malloc((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	if (fill(str, (char *)s, c, count))
		return (NULL);
	return (str);
}
