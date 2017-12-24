/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:54:39 by adleau            #+#    #+#             */
/*   Updated: 2017/12/24 20:21:47 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDELBROT_H
# define MANDELBROT_H
# include <general.h>
# include <shortcuts.h>

typedef struct	s_params
{
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	double	zoomx;
	double	zoomy;
}				t_params;

typedef struct	s_mand
{
	int			**win_tab;
	t_env		*env;
	t_params	*par;
}				t_mand;

void			mandelbrot(void);
void			mand_draw(t_mand *mand);
void			free_mand(t_mand *mand, int par);
void		mlx_pixel_put_to_image(void *img, t_uint x, t_uint y, t_uint color);
#endif
