/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:51:30 by adleau            #+#    #+#             */
/*   Updated: 2018/01/04 12:36:19 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fractal.h>

int			main(int ac, char **av)
{
	if (ac == 2)
	{
		if (!(ft_strcmp(av[1], "mandelbrot")))
			mandelbrot();
		if (!(ft_strcmp(av[1], "julia")))
			julia();
		if (!(ft_strcmp(av[1], "buddha")))
			;
	}
	ft_putendl("Usage : ./fractol [mandelbrot || julia || buddha]");
	return (0);
}
