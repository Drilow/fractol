/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 12:35:05 by adleau            #+#    #+#             */
/*   Updated: 2018/01/04 12:54:22 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fractal.h>
#include <mlx.h>
#include <shortcuts.h>

void		draw_annex_j(t_frac *jul, int x, int y)
{
	double	c_r;
	double	c_i;
	double	z_r;
	double	z_i;
	double	tmp;
	int		i;

	c_r = 0.285;
	c_i = 0.01;
	z_r = x / jul->par->zoomx + jul->par->x1;
	z_i = y / jul->par->zoomy + jul->par->y1;
	i = -1;
	tmp = 0;
	while (z_r * z_r + z_i * z_i < 4 && ++i < MAX_IT * jul->par->it)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * tmp * z_i + c_i;
	}
	jul->eq_tab[y][x].x = c_r;
	jul->eq_tab[y][x].y = c_i;
	if (i < MAX_IT * jul->par->it)
		jul->win_tab[y][x] = jul->par->color[i];
}

void		draw_win_j(t_frac *jul)
{
	t_uint	x;
	t_uint	y;

	y = -1;
	while (++y < WIN_HT)
	{
		x = -1;
		while (++x < WIN_WD)
		{
			mlx_pixel_put_to_image(jul->env->img, x, y, jul->win_tab[y][x]);
		}
	}
	mlx_put_image_to_window(jul->env->mlx, jul->env->win, jul->env->img, 0, 0);
}

void		redraw_j(t_frac *jul)
{
	int		x;
	int		y;

	x = -1;
	while (++x < WIN_WD)
	{
		y = -1;
		while (++y < WIN_HT)
			draw_annex_j(jul, x, y);
	}
	draw_win_j(jul);
}

void		init_par_jul(t_frac *jul)
{
	int		i;

	jul->par->x1 = -2;
	jul->par->x2 = 2;
	jul->par->y1 = -2;
	jul->par->y2 = 2;
	jul->par->zoomx = WIN_WD / (jul->par->x2 - jul->par->x1);
	jul->par->zoomy = WIN_HT / (jul->par->y2 - jul->par->y1);
	jul->par->it = 1;
	jul->par->mul = .075;
	if (!(jul->par->color = (int*)malloc(sizeof(int) * MAX_IT)))
		free_frac(jul, 1);
	i = -1;
	while (++i < MAX_IT)
		jul->par->color[i] = 0xFF / MAX_IT * i;
}

int			mousehook_j(int button, int x, int y, t_frac *mand)
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
		redraw_j(mand);
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
		redraw_j(mand);
	}
	return (0);
}


void		jul_draw(t_frac *jul)
{
	redraw_j(jul);
	mlx_key_hook(jul->env->win, keyhook_f, jul);
	mlx_mouse_hook(jul->env->win, mousehook_j, jul);
	mlx_loop(jul->env->mlx);
}

void			julia(void)
{
	t_frac		jul;

	jul.win_tab = NULL;
	if (!(jul.win_tab = init_wintab()))
		return ;
	jul.eq_tab = NULL;
	if (!(jul.eq_tab = init_eqtab()))
		return ;
	jul.env = NULL;
	if (!(jul.env = (t_env*)malloc(sizeof(t_env))))
		free_frac(&jul, 1);
	init_env(&jul);
	jul.par = NULL;
	if (!(jul.par = (t_params*)malloc(sizeof(t_params))))
		free_frac(&jul, 1);
	init_par_jul(&jul);
	jul_draw(&jul);
}
