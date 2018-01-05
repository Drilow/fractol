/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 11:39:10 by adleau            #+#    #+#             */
/*   Updated: 2018/01/05 13:54:59 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifndef FRACTAL_H
# define FRACTAL_H
# include <general.h>
# include <shortcuts.h>
# include <libft.h>

typedef struct	s_c
{
	double	c_r;
	double	c_i;
}				t_c;

typedef struct	s_z
{
	double	z_r;
	double	z_i;
}				t_z;

typedef struct	s_params
{
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	t_c		*c;
	int		ind;
	double	zoomx;
	double	zoomy;
	double	it;
	double	mul;
	int		*color;
}				t_params;

typedef struct	s_vec
{
	double	x;
	double	y;
}				t_vec;

typedef struct	s_frac
{
	int			**win_tab;
	t_vec		**eq_tab;
	t_env		*env;
	t_params	*par;
	char		*av;
	int			lock;
	void		(*f)(struct s_frac*, int, int);
}				t_frac;

void			mandelbrot(void);
void			julia(void);
void			buddha(void);
void			draw(t_frac *frac);
void			free_mand(t_frac *mand, int par);
void			mlx_pixel_put_to_image(void *img, t_uint x, t_uint y,
				t_uint color);
void			init_par_mand(t_frac *mand);
int				**init_wintab(void);
void			init_env(t_frac *mand);
t_vec			**init_eqtab(void);
void			free_frac(t_frac *mand, int par);
int				keyhook_f(int keycode, t_frac *mand);
int				mousehook_f(int button, int x, int y, t_frac *mand);
void			julia_annex(t_frac *jul, int x, int y);
void			mand_annex(t_frac *mand, int x, int y);
void			begin(void (*f)(t_frac*, int, int), char *av);
void			shitfrac_annex(t_frac *frac, int x, int y);

#endif
