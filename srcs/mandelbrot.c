/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:54:06 by adleau            #+#    #+#             */
/*   Updated: 2017/12/25 07:05:10 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mandelbrot.h>
#include <libft.h>
#include <mlx.h>

void			free_mand(t_mand *mand, int par)
{
	int			i;

	i = -1;
	while (++i < WIN_HT)
		free(mand->win_tab[i]);
	free(mand->win_tab);
	if (mand->env)
	{
		if (mand->env->mlx)
			free(mand->env->mlx);
		if (mand->env->win)
			free(mand->env->win);
		if (mand->env->img)
			free(mand->env->img);
	}
	exit(par);
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

void			init_env(t_mand *mand)
{
	if (!(mand->env->mlx = mlx_init()))
		free_mand(mand, 1);
	if (!(mand->env->win = mlx_new_window(mand->env->mlx, WIN_WD, WIN_HT, "fractol")))
		free_mand(mand, 1);
	if (!(mand->env->img = mlx_new_image(mand->env->mlx, WIN_WD, WIN_HT)))
		free_mand(mand, 1);
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

void			mandelbrot(void)
{
	t_mand		*mand;

	if (!(mand = (t_mand*)malloc(sizeof(t_mand))))
		return ;
	if (!(mand->win_tab = init_wintab()))
		return ;
	if (!(mand->eq_tab = init_eqtab()))
		return ;
	if (!(mand->env = (t_env*)malloc(sizeof(t_env))))
		free_mand(mand, 1);
	init_env(mand);
	if (!(mand->par = (t_params*)malloc(sizeof(t_params))))
		free_mand(mand, 1);
	init_par(mand);
	mand_draw(mand);
}
