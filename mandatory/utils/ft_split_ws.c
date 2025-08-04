
#include "../cub3D.h"

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
	str = (char **)malloc((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	if (fill(str, (char *)s, count))
		return (NULL);
	return (str);
}
