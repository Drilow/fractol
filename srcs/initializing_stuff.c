/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing_stuff.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 11:36:01 by adleau            #+#    #+#             */
/*   Updated: 2018/01/08 15:01:09 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractal.h>
#include <mlx.h>

void		init_ctab(t_c *c)
{
	c[0].c_r = -0.75;
	c[0].c_i = 0.1;
	c[1].c_r = 0.285;
	c[1].c_i = 0.01;
	c[2].c_r = 0.13;
	c[2].c_i = 0.745;
	c[3].c_r = 0.4;
	c[3].c_i = 0.2;
	c[4].c_r = -1;
	c[4].c_i = 0;
	c[5].c_r = 0.5;
	c[5].c_i = 0.5;
	c[6].c_r = 0.3;
	c[6].c_i = 0.5;
	c[7].c_r = 0.185;
	c[7].c_i = 0.013;
}

void		init_params(t_frac *frac)
{
	frac->par->x1 = -2;
	frac->par->x2 = 2;
	frac->par->y1 = -2;
	frac->par->y2 = 2;
	frac->par->zoomx = WIN_WD / (frac->par->x2 - frac->par->x1);
	frac->par->zoomy = WIN_HT / (frac->par->y2 - frac->par->y1);
	frac->par->it = 1;
	frac->par->mul = 1;
	frac->par->ind = 0;
	frac->par->mx = 0;
	frac->par->my = 0;
	init_ctab(frac->par->c);
}

void		init_par(t_frac *frac)
{
	int		i;

	if (!(frac->par->c = (t_c*)malloc(sizeof(t_c) * 8)))
		free_frac(frac, 1);
	init_params(frac);
	if (!(frac->par->color = (int*)malloc(sizeof(int) * MAX_IT)))
		free_frac(frac, 1);
	i = -1;
	while (++i < MAX_IT)
		frac->par->color[i] = 0xFFFFFF / MAX_IT * i;
}

void			begin(void (*f)(t_frac*, int, int), char *av)
{
	t_frac		frac;

	frac.win_tab = NULL;
	frac.av = av;
	frac.lock = 0;
	if (!(frac.win_tab = init_wintab()))
		return ;
	frac.eq_tab = NULL;
	if (!(frac.eq_tab = init_eqtab()))
		return ;
	frac.env = NULL;
	if (!(frac.env = (t_env*)malloc(sizeof(t_env))))
		free_frac(&frac, 1);
	init_env(&frac);
	frac.par = NULL;
	if (!(frac.par = (t_params*)malloc(sizeof(t_params))))
		free_frac(&frac, 1);
	init_par(&frac);
	frac.f = (*f);
	draw(&frac);
}

int				**init_wintab(void)
{
	int			**tab;
	int			i;

	tab = NULL;
	if (!(tab = (int**)malloc(sizeof(int*) * WIN_HT)))
		return (NULL);
	i = -1;
	while (++i <= WIN_HT)
	{
		if (!(tab[i] = (int*)malloc(sizeof(int) * WIN_WD)))
			return (NULL);
		ft_bzero(tab[i], WIN_WD);
	}
	return (tab);
}

void			init_env(t_frac *frac)
{
	frac->env->mlx = NULL;
	frac->env->win = NULL;
	frac->env->img = NULL;
	if (!(frac->env->mlx = mlx_init()))
		free_frac(frac, 1);
	if (!(frac->env->win = mlx_new_window(frac->env->mlx, WIN_WD, WIN_HT, "fractol")))
		free_frac(frac, 1);
	if (!(frac->env->img = mlx_new_image(frac->env->mlx, WIN_WD, WIN_HT)))
		free_frac(frac, 1);
}

t_vec			**init_eqtab(void)
{
	int			i;
	int			j;
	t_vec		**tab;

	i = -1;
	if (!(tab = (t_vec**)malloc(sizeof(t_vec*) * WIN_HT)))
		return (NULL);
	while (++i < WIN_HT)
	{
		j = -1;
		if (!(tab[i] = (t_vec*)malloc(sizeof(t_vec) * WIN_WD)))
			return (NULL);
		while (++j < WIN_WD)
		{
			tab[i][j].x = 0;
			tab[i][j].y = 0;
		}
	}
	return (tab);
}
