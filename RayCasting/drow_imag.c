/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_imag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:05:33 by obarais           #+#    #+#             */
/*   Updated: 2025/07/13 16:31:54 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	drow_imag_in(t_game **g, int x, int *y, int start)
{
	int i = round((*g)->ofs_tex);
	double j = 0.0;
	char *im;
	char *dst;

	while (*y <= start + (*g)->wall_height && *y <= WIN_HEIGHT)
	{
		j = ((double)(*g)->imag_height / (*g)->wall_height) * (*y - start);
		if (j <= (*g)->imag_height)
			dst = (*g)->d_nsew + ((int)j * (*g)->psl + i * ((*g)->pbpp / 8));
		if ((*g)->ng == 5 || (*y < 2 || *y >= 8 + MINMAP_HE) || (x < 2 || x >= 8 + MINMAP_WI))
		{
			if (*y <= WIN_HEIGHT)
			{
				im = (*g)->d_imag_v + ((*y) * (*g)->sl + x *((*g)->bpp / 8));
				*(unsigned int *)im = *(unsigned int *)dst;
			}
		}
		(*y)++;
	}
}
