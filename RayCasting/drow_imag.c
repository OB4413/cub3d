/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_imag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obarais <obarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:05:33 by obarais           #+#    #+#             */
/*   Updated: 2025/07/10 10:22:50 by obarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	wall_height_imag(t_game **g, int x, int *y, int start)
{
	double m = (double)(*g)->wall_height / (*g)->imag_height;
	int i = round((*g)->ofs_tex);
	int j, k, d;
	char *dst;
	char *st;
	char *im;

	j = 0;
	while ((*y) <= start + (*g)->wall_height)
	{
		k = 1;
		dst = (*g)->d_nsew + (j * (*g)->psl + i * ((*g)->pbpp / 8));
		while (j <= (*g)->imag_height)
		{
			j++;
			st = (*g)->d_nsew + (j * (*g)->psl + i * ((*g)->pbpp / 8));
			if (*(unsigned int *)dst != *(unsigned int *)st)
				break;
			k++;
		}
		d = *y;
		while ((*y) <= d + (k * m) && (*y) <= start + (*g)->wall_height)
		{
			if ((*g)->ng == 5 || (*y < 2 || *y >= 8 + MINMAP_HE) || (x < 2 || x >= 8 + MINMAP_WI))
			{
				im = (*g)->d_imag_v + ((*y) * (*g)->sl + x *((*g)->bpp / 8));
				*(unsigned int *)im = *(unsigned int *)dst;
			}
			(*y)++;
		}
	}
}


void	imag_height_wall(t_game **g, int x, int *y, int start)
{
	double m = (double)(*g)->imag_height / (*g)->wall_height;
	int l = round((*g)->ofs_tex);
	int j, k, d;
	char *dst;
	char *st;
	char *im;

	j = 0;
	while ((*y) <= start + (*g)->wall_height)
	{
		k = 1;
		dst = (*g)->d_nsew + (j * (*g)->psl + l * ((*g)->pbpp / 8));
		while (j <= (*g)->imag_height)
		{
			j++;
			st = (*g)->d_nsew + (j * (*g)->psl + l * ((*g)->pbpp / 8));
			if (*(unsigned int *)dst != *(unsigned int *)st)
				break;
			k++;
		}
		d = *y;
		while ((*y) <= d + (k / m) && (*y) <= start + (*g)->wall_height)
		{
			if ((*g)->ng == 5 || (*y < 2 || *y >= 8 + MINMAP_HE) || (x < 2 || x >= 8 + MINMAP_WI))
			{
				im = (*g)->d_imag_v + ((*y) * (*g)->sl + x *((*g)->bpp / 8));
				*(unsigned int *)im = *(unsigned int *)dst;
			}
			(*y)++;
		}
	}
}
