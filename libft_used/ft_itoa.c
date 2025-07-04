/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:04:06 by sodahani          #+#    #+#             */
/*   Updated: 2025/05/01 23:39:49 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_len_int(long n)
{
	int	i;
	int	j;

	j = 0;
	while (n > 0)
	{
		i = n % 10;
		n = n - i;
		n = n / 10;
		j++;
	}
	return (j);
}

static char	*ft_cpy_int(char *array, long n, int j, int k)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		if (k == 1)
		{
			array[0] = '-';
			k = 0;
		}
		i = n % 10;
		array[j] = i + '0';
		n = n - i;
		n = n / 10;
		j--;
	}
	return (array);
}

char	*ft_itoa(int n)
{
	int		i;
	int		j;
	int		k;
	long	b;
	char	*array;

	i = 0;
	k = 0;
	j = 0;
	b = n;
	if (b <= 0)
	{
		b = b * (-1);
		j++;
		k++;
	}
	j = j + ft_len_int(b);
	array = calloc(j + 1, sizeof(char));
	if (array == NULL)
		return (NULL);
	if (n == 0)
		array[0] = '0';
	array[j] = '\0';
	j--;
	return (ft_cpy_int(array, b, j, k));
}
