/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 19:26:49 by adleau            #+#    #+#             */
/*   Updated: 2017/12/24 20:24:01 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mandelbrot.h>
#include <mlx.h>
#include <shortcuts.h>

void		draw_annex(t_mand *mand, int x, int y)
{
	double	c_r;
	double	c_i;
	double	z_r;
	double	z_i;
	double	tmp;
	int		i;

	c_r = x / mand->par->zoomx + mand->par->x1;
	c_i = y / mand->par->zoomy + mand->par->y1;
	z_r = 0;
	z_i = 0;
	i = -1;
	tmp = 0;
	while (z_r * z_r + z_i * z_i < 4 && ++i < MAX_IT)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * tmp * z_i + c_i;
	}
	if (i == MAX_IT)
	mand->win_tab[y][x] = 0xFFFFFF;
	else
		mand->win_tab[y][x] = 0xFF0000;
}

void		init_par(t_mand *mand)
{
	mand->par->x1 = -2.1;
	mand->par->x2 = 0.6;
	mand->par->y1 = -1.2;
	mand->par->y2 = 1.2;
	mand->par->zoomx = WIN_WD / (mand->par->x2 - mand->par->x1);
	mand->par->zoomy = WIN_HT / (mand->par->y2 - mand->par->y1);
}

void		draw_win(t_mand *mand)
{
	t_uint	x;
	t_uint	y;

	y = -1;
	while (++y < WIN_HT)
	{
		x = -1;
		while (++x < WIN_WD)
		{
			mlx_pixel_put_to_image(mand->env->img, x, y, mand->win_tab[y][x]);
		}
	}
	mlx_put_image_to_window(mand->env->mlx, mand->env->win, mand->env->img, 0, 0);
}

void		redraw(t_mand *mand)
{
	int		x;
	int		y;

	if (!(mand->par = (t_params*)malloc(sizeof(t_params))))
		free_mand(mand, 1);
	init_par(mand);
	x = -1;
	while (++x < WIN_WD)
	{
		y = -1;
		while (++y < WIN_HT)
			draw_annex(mand, x, y);
	}
	draw_win(mand);
}

int			keyhook_f(int keycode, t_mand *mand)
{
	if (keycode == 53)
		free_mand(mand, 0);
	return (0);
}

void		mand_draw(t_mand *mand)
{
	redraw(mand);
	mlx_key_hook(mand->env->win, keyhook_f, mand);

	mlx_loop(mand->env->mlx);
}
