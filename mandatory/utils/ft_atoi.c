#include "../cub3D.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	long	results;

	i = 0;
	sign = 1;
	results = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		results = (results * 10) + (str[i] - '0');
		if (results < 0)
			return (-sign * (sign == 1));
		i++;
	}
	return (results * sign);
}
