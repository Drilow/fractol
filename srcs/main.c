/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:51:30 by adleau            #+#    #+#             */
/*   Updated: 2017/12/24 18:55:18 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mandelbrot.h>

int			main(int ac, char **av)
{
	if (ac == 2)
	{
		if (!(ft_strcmp(av[1], "mandelbrot")))
			mandelbrot();
		if (!(ft_strcmp(av[1], "julia")))
			;
		if (!(ft_strcmp(av[1], "ensemble")))
			;
	}
	return (0);
}
