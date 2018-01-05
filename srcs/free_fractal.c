/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 11:38:36 by adleau            #+#    #+#             */
/*   Updated: 2018/01/04 14:38:47 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractal.h>

void			free_frac(t_frac *mand, int par)
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
