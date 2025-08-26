/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:38:08 by ynadime           #+#    #+#             */
/*   Updated: 2025/08/26 11:22:00 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*newstr;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_strchr(set, s1[len - 1]))
		len--;
	newstr = (char *)ft_malloc((len + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, len + 1);
	return (newstr);
}
