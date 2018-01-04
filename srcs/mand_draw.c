/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 19:26:49 by adleau            #+#    #+#             */
/*   Updated: 2018/01/04 12:54:47 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fractal.h>
#include <mlx.h>
#include <shortcuts.h>

void		draw_annex(t_frac *mand, int x, int y)
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
	while (z_r * z_r + z_i * z_i < 4 && ++i < MAX_IT * mand->par->it)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * tmp * z_i + c_i;
	}
	mand->eq_tab[y][x].x = c_r;
	mand->eq_tab[y][x].y = c_i;
	if (i < MAX_IT * mand->par->it)
		mand->win_tab[y][x] = mand->par->color[i];
}

void		draw_win(t_frac *mand)
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

void		redraw(t_frac *mand)
{
	int		x;
	int		y;

	x = -1;
	while (++x < WIN_WD)
	{
		y = -1;
		while (++y < WIN_HT)
			draw_annex(mand, x, y);
	}
	draw_win(mand);
}

int			keyhook_f(int keycode, t_frac *mand)
{
	if (keycode == 53)
		free_frac(mand, 0);
	return (0);
}

int			mousehook_f(int button, int x, int y, t_frac *mand)
{
	int		i;
	int		j;

	if (y < 0 || x < 0)
		return (0);
	i = -1;
	if (button == 1)
	{
		mand->par->it += 1;
		mand->par->x1 = mand->eq_tab[y][x].x - mand->par->mul;
		mand->par->x2 = mand->eq_tab[y][x].x + mand->par->mul;
		mand->par->y1 = mand->eq_tab[y][x].y - mand->par->mul;
		mand->par->y2 = mand->eq_tab[y][x].y + mand->par->mul;
		mand->par->mul /= 5;
		while (++i < WIN_HT)
		{
			j = -1;
			while (++j < WIN_WD)
			{
				mand->win_tab[i][j] = 0;
				mand->eq_tab[i][j].x = 0;
				mand->eq_tab[i][j].y = 0;
			}
		}
		mand->par->zoomx = WIN_WD / (mand->par->x2 - mand->par->x1);
		mand->par->zoomy = WIN_HT / (mand->par->y2 - mand->par->y1);
		redraw(mand);
	}
	if (button == 2)
	{
		mand->par->x1 = mand->eq_tab[y][x].x + mand->par->mul;
		mand->par->x2 = mand->eq_tab[y][x].x - mand->par->mul;
		mand->par->y1 = mand->eq_tab[y][x].y + mand->par->mul;
		mand->par->y2 = mand->eq_tab[y][x].y - mand->par->mul;
		mand->par->mul *= 10;
		while (++i < WIN_HT)
		{
			j = -1;
			while (++j < WIN_WD)
			{
				mand->win_tab[i][j] = 0;
				mand->eq_tab[i][j].x = 0;
				mand->eq_tab[i][j].y = 0;
			}
		}
		if (mand->par->it > 1)
			mand->par->it -= 1;
		mand->par->zoomx = WIN_WD / (mand->par->x2 - mand->par->x1);
		mand->par->zoomy = WIN_HT / (mand->par->y2 - mand->par->y1);
		redraw(mand);
	}
	return (0);
}

void		mand_draw(t_frac *mand)
{
	redraw(mand);
	mlx_key_hook(mand->env->win, keyhook_f, mand);
	mlx_mouse_hook(mand->env->win, mousehook_f, mand);
	mlx_loop(mand->env->mlx);
}
