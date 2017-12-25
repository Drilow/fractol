/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 19:26:49 by adleau            #+#    #+#             */
/*   Updated: 2017/12/25 09:39:10 by adleau           ###   ########.fr       */
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

void		init_par(t_mand *mand)
{
	int		i;

	mand->par->x1 = -2.1;
	mand->par->x2 = 0.6;
	mand->par->y1 = -1.2;
	mand->par->y2 = 1.2;
	mand->par->zoomx = WIN_WD / (mand->par->x2 - mand->par->x1);
	mand->par->zoomy = WIN_HT / (mand->par->y2 - mand->par->y1);
	mand->par->it = 1;
	if (!(mand->par->color = (int*)malloc(sizeof(int) * MAX_IT)))
		free_mand(mand, 1);
	i = -1;
	while (++i < MAX_IT)
		mand->par->color[i] = 0xFF / MAX_IT * i;
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

int			mousehook_f(int button, int __attribute__((unused))x, int __attribute__((unused))y, t_mand *mand)
{
	int		i;
	int		j;

	i = -1;
	printf("%d || %d %d || %f %f\n", button, x, y, mand->eq_tab[y][x].x, mand->eq_tab[y][x].y);
	// 5 up 4 down
	if (button == 1)
	{
		mand->par->it *= 2;
		mand->par->x1 = mand->eq_tab[y][x].x - .005;
		mand->par->x2 = mand->eq_tab[y][x].x + .005;
		mand->par->y1 = mand->eq_tab[y][x].y - .005;
		mand->par->y2 = mand->eq_tab[y][x].y + .005;
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
		mand->par->zoomx *= 2;
		mand->par->zoomy *= 2;
		redraw(mand);
	}
	if (button == 2)
	{
		mand->par->x1 = mand->eq_tab[y][x].x + .005;
		mand->par->x2 = mand->eq_tab[y][x].x - .005;
		mand->par->y1 = mand->eq_tab[y][x].y + .005;
		mand->par->y2 = mand->eq_tab[y][x].y - .005;
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
		if (mand->par->it != 1)
			mand->par->it /= 2;
		mand->par->zoomx = WIN_WD / (mand->par->x2 - mand->par->x1);
		mand->par->zoomy = WIN_HT / (mand->par->y2 - mand->par->y1);
		mand->par->zoomx /= 2;
		mand->par->zoomy /= 2;
		redraw(mand);
	}
	return (0);
}

void		mand_draw(t_mand *mand)
{
	redraw(mand);
	mlx_key_hook(mand->env->win, keyhook_f, mand);
	mlx_mouse_hook(mand->env->win, mousehook_f, mand);
	mlx_loop(mand->env->mlx);
}
