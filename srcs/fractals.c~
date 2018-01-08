/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:23:41 by adleau            #+#    #+#             */
/*   Updated: 2018/01/05 14:25:10 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fractal.h>
#include <mlx.h>
#include <shortcuts.h>

void		julia_annex(t_frac *jul, int x, int y)
{
	t_c		c;
	t_z		z;
	double	tmp;
	int		i;

	c = jul->par->c[jul->par->ind];
	z.z_r = x / jul->par->zoomx + jul->par->x1;
	z.z_i = y / jul->par->zoomy + jul->par->y1;
	i = -1;
	tmp = 0;
	while (z.z_r * z.z_r + z.z_i * z.z_i < 4 && ++i < MAX_IT * jul->par->it)
	{
		tmp = z.z_r;
		z.z_r = z.z_r * z.z_r - z.z_i * z.z_i + c.c_r;
		z.z_i = 2 * tmp * z.z_i + c.c_i;
	}
	jul->eq_tab[y][x].x = c.c_r;
	jul->eq_tab[y][x].y = c.c_i;
	if (i < MAX_IT * jul->par->it)
		jul->win_tab[y][x] = jul->par->color[i];
}

void		shitfrac_annex(t_frac *frac, int x, int y)
{
	t_c		c;
	t_z		z;
	double	tmp;
	int		i;

	c.c_r = x / frac->par->zoomx + frac->par->x1;
	c.c_i = y / frac->par->zoomy + frac->par->y1;
	z.z_r = frac->par->c[1].c_r;
	z.z_i = (y / frac->par->zoomy + frac->par->y1);
	i = -1;
	tmp = 0;
	while (z.z_r * z.z_r + z.z_i * z.z_i < 4 && ++i < MAX_IT * frac->par->it)
	{
		tmp = z.z_r;
		z.z_r = z.z_r * z.z_r - z.z_i * z.z_i + c.c_r;
		z.z_i = 2 * tmp * z.z_i + c.c_i;
	}
	frac->eq_tab[y][x].x = c.c_r;
	frac->eq_tab[y][x].y = c.c_i;
	if (i < MAX_IT * frac->par->it)
		frac->win_tab[y][x] = frac->par->color[i];
}

void		mand_annex(t_frac *mand, int x, int y)
{
	t_c		c;
	t_z		z;
	double	tmp;
	int		i;

	c.c_r = x / mand->par->zoomx + mand->par->x1;
	c.c_i = y / mand->par->zoomy + mand->par->y1;
	z.z_r = 0;
	z.z_i = 0;
	i = -1;
	tmp = 0;
	while (z.z_r * z.z_r + z.z_i * z.z_i < 4 && ++i < MAX_IT * mand->par->it)
	{
		tmp = z.z_r;
		z.z_r = z.z_r * z.z_r - z.z_i * z.z_i + c.c_r;
		z.z_i = 2 * tmp * z.z_i + c.c_i;
	}
	mand->eq_tab[y][x].x = c.c_r;
	mand->eq_tab[y][x].y = c.c_i;
	if (i < MAX_IT * mand->par->it)
		mand->win_tab[y][x] = mand->par->color[i];
}
