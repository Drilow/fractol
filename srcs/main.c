/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:51:30 by adleau            #+#    #+#             */
/*   Updated: 2018/01/05 13:54:21 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fractal.h>

int			main(int ac, char **av)
{
	if (ac == 2)
	{
		if (!(ft_strcmp(av[1], "mandelbrot")))
			begin(mand_annex, av[1]);
		if (!(ft_strcmp(av[1], "julia")))
			begin(julia_annex, av[1]);
		if (!(ft_strcmp(av[1], "shit")))
			begin(shitfrac_annex, av[1]);
	}
	ft_putendl("Usage : ./fractol [mandelbrot || julia || buddha]");
	return (0);
}
