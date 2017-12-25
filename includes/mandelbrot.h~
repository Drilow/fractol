/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:54:39 by adleau            #+#    #+#             */
/*   Updated: 2017/12/25 06:56:51 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDELBROT_H
# define MANDELBROT_H
# include <general.h>
# include <shortcuts.h>
# include <libft.h>

typedef struct	s_params
{
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	double	zoomx;
	double	zoomy;
	double	it;
	int		*color;
}				t_params;

typedef struct	s_vec
{
	double		x;
	double		y;
}				t_vec;

typedef struct	s_mand
{
	int			**win_tab;
	t_vec		**eq_tab;
	t_env		*env;
	t_params	*par;
}				t_mand;

void			mandelbrot(void);
void			mand_draw(t_mand *mand);
void			free_mand(t_mand *mand, int par);
void			mlx_pixel_put_to_image(void *img, t_uint x, t_uint y, t_uint color);
void			init_par(t_mand *mand);

#endif
