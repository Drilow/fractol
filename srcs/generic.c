/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:24:05 by adleau            #+#    #+#             */
/*   Updated: 2018/01/08 13:04:57 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fractal.h>
#include <mlx.h>
#include <shortcuts.h>

void		draw_win(t_frac *frac)
{
	t_uint	x;
	t_uint	y;

	y = -1;
	while (++y < WIN_HT)
	{
		x = -1;
		while (++x < WIN_WD)
			mlx_pixel_put_to_image(frac->env->img, x, y, frac->win_tab[y][x]);
	}
	mlx_put_image_to_window(frac->env->mlx, frac->env->win, frac->env->img, 0, 0);
}

void		redraw(t_frac *frac)
{
	int		x;
	int		y;

	x = -1;
	while (++x < WIN_WD)
	{
		y = -1;
		while (++y < WIN_HT)
			frac->f(frac, x, y);
	}
	draw_win(frac);
}

int			get_keys(int keycode)
{
	if (keycode == KEY_1)
		return (1);
	else if(keycode == KEY_2)
		return (2);
	else if(keycode == KEY_3)
		return (3);
	else if(keycode == KEY_4)
		return (4);
	else if(keycode == KEY_5)
		return (5);
	else if(keycode == KEY_6)
		return (6);
	else if(keycode == KEY_7)
		return (7);
	else if(keycode == KEY_8)
		return (8);
	return (0);
}

int			keyhook_f(int keycode, t_frac *frac)
{
	int		i;
	int		j;

	if (keycode == 53)
		free_frac(frac, 0);
	if (keycode == 37)
	{
		if (frac->lock == 0)
			frac->lock = 1;
		else
			frac->lock = 0;
	}
	if (get_keys(keycode))
	{
		i = -1;
		while (++i < WIN_HT)
		{
			j = -1;
			while (++j < WIN_WD)
			{
				frac->win_tab[i][j] = 0;
				frac->eq_tab[i][j].x = 0;
				frac->eq_tab[i][j].y = 0;
			}
		}
		mlx_destroy_image(frac->env->mlx, frac->env->img);
		frac->env->img = NULL;
		if (!(frac->env->img = mlx_new_image(frac->env->mlx, WIN_WD, WIN_HT)))
			free_frac(frac, 1);
		init_params(frac);
		frac->par->ind = get_keys(keycode) - 1;
		redraw(frac);
	}
	return (0);
}

void		zoom_in(t_frac *frac, int x, int y)
{
	int		i;
	int		j;

	i = -1;
	frac->par->it += 1;
	frac->par->x1 = frac->eq_tab[y][x].x - frac->par->mul;
	frac->par->x2 = frac->eq_tab[y][x].x + frac->par->mul;
	frac->par->y1 = frac->eq_tab[y][x].y - frac->par->mul;
	frac->par->y2 = frac->eq_tab[y][x].y + frac->par->mul;
	frac->par->mul /= 10;
	printf("%f %f %f %f\n", frac->par->x1, frac->par->x2, frac->par->y1, frac->par->y2);
	while (++i < WIN_HT)
	{
		j = -1;
		while (++j < WIN_WD)
		{
			frac->win_tab[i][j] = 0;
			frac->eq_tab[i][j].x = 0;
			frac->eq_tab[i][j].y = 0;
		}
	}
	frac->par->zoomx = WIN_WD / (frac->par->x2 - frac->par->x1);
	frac->par->zoomy = WIN_HT / (frac->par->y2 - frac->par->y1);
}

void		zoom_out(t_frac *frac, int x, int y)
{
	int		i;
	int		j;

	i = -1;
	frac->par->x1 = frac->eq_tab[y][x].x + frac->par->mul;
	frac->par->x2 = frac->eq_tab[y][x].x - frac->par->mul;
	frac->par->y1 = frac->eq_tab[y][x].y + frac->par->mul;
	frac->par->y2 = frac->eq_tab[y][x].y - frac->par->mul;
	frac->par->mul *= 10;
	while (++i < WIN_HT)
	{
		j = -1;
		while (++j < WIN_WD)
		{
			frac->win_tab[i][j] = 0;
			frac->eq_tab[i][j].x = 0;
			frac->eq_tab[i][j].y = 0;
		}
	}
	if (frac->par->it > 1)
		frac->par->it -= 1;
	frac->par->zoomx = WIN_WD / (frac->par->x2 - frac->par->x1);
	frac->par->zoomy = WIN_HT / (frac->par->y2 - frac->par->y1);
}

int			mousehook_f(int button, int x, int y, t_frac *frac)
{
	if (y < 0 || x < 0)
		return (0);
	if (button == 1)
	{
		zoom_in(frac, x, y);
		redraw(frac);
	}
	if (button == 2)
	{
		zoom_out(frac, x, y);
		redraw(frac);
	}
	return (0);
}

int			mouse_mv(int x, int y, t_frac *frac)
{
	int		i;
	int		j;

	if (frac->lock == 0)
	{
		if (x > frac->par->mx)
			frac->par->c[frac->par->ind].c_r += 0.005;
		else if (x < frac->par->mx)
			frac->par->c[frac->par->ind].c_r -= 0.005;
		if (y < frac->par->my)
			frac->par->c[frac->par->ind].c_i += 0.005;
		else if (y > frac->par->my)
			frac->par->c[frac->par->ind].c_i -= 0.005;
		frac->par->mx = x;
		frac->par->my = y;
		i = -1;
		while (++i < WIN_HT)
		{
			j = -1;
			while (++j < WIN_WD)
			{
				frac->win_tab[i][j] = 0;
				frac->eq_tab[i][j].x = 0;
				frac->eq_tab[i][j].y = 0;
			}
		}
		redraw(frac);
	}
	return (0);
}

void		draw(t_frac *frac)
{
	redraw(frac);
	mlx_key_hook(frac->env->win, keyhook_f, frac);
	if (!ft_strcmp(frac->av, "julia") && frac->lock == 0)
		mlx_hook(frac->env->win, 6, 1L<<6, mouse_mv, frac);
	mlx_mouse_hook(frac->env->win, mousehook_f, frac);
	mlx_loop(frac->env->mlx);
}

