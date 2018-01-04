/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing_stuff.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 11:36:01 by adleau            #+#    #+#             */
/*   Updated: 2018/01/04 12:38:20 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractal.h>
#include <mlx.h>

void		init_par_mand(t_frac *mand)
{
	int		i;

	mand->par->x1 = -2;
	mand->par->x2 = 2;
	mand->par->y1 = -2;
	mand->par->y2 = 2;
	mand->par->zoomx = WIN_WD / (mand->par->x2 - mand->par->x1);
	mand->par->zoomy = WIN_HT / (mand->par->y2 - mand->par->y1);
	mand->par->it = 1;
	mand->par->mul = .075;
	if (!(mand->par->color = (int*)malloc(sizeof(int) * MAX_IT)))
		free_frac(mand, 1);
	i = -1;
	while (++i < MAX_IT)
		mand->par->color[i] = 0xFF / MAX_IT * i;
}

void			mandelbrot(void)
{
	t_frac		mand;

	mand.win_tab = NULL;
	if (!(mand.win_tab = init_wintab()))
		return ;
	mand.eq_tab = NULL;
	if (!(mand.eq_tab = init_eqtab()))
		return ;
	mand.env = NULL;
	if (!(mand.env = (t_env*)malloc(sizeof(t_env))))
		free_frac(&mand, 1);
	init_env(&mand);
	mand.par = NULL;
	if (!(mand.par = (t_params*)malloc(sizeof(t_params))))
		free_frac(&mand, 1);
	init_par_mand(&mand);
	mand_draw(&mand);
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

void			init_env(t_frac *mand)
{
	mand->env->mlx = NULL;
	mand->env->win = NULL;
	mand->env->img = NULL;
	if (!(mand->env->mlx = mlx_init()))
		free_frac(mand, 1);
	if (!(mand->env->win = mlx_new_window(mand->env->mlx, WIN_WD, WIN_HT, "fractol")))
		free_frac(mand, 1);
	if (!(mand->env->img = mlx_new_image(mand->env->mlx, WIN_WD, WIN_HT)))
		free_frac(mand, 1);
}

t_vec			**init_eqtab(void)
{
	int			i;
	int			j;
	t_vec		**tab;

	i = -1;
	if (!(tab = (t_vec**)malloc(sizeof(t_vec*) * WIN_HT)))
		return (NULL);
	while (++i < WIN_WD)
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
