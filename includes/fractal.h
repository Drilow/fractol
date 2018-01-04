/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 11:39:10 by adleau            #+#    #+#             */
/*   Updated: 2018/01/04 12:50:32 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
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
	double	mul;
	int		*color;
}				t_params;

typedef struct	s_vec
{
	double		x;
	double		y;
}				t_vec;

typedef struct	s_frac
{
	int			**win_tab;
	t_vec		**eq_tab;
	t_env		*env;
	t_params	*par;
}				t_frac;

void			mandelbrot(void);
void			julia(void);
void			mand_draw(t_frac *mand);
void			free_mand(t_frac *mand, int par);
void			mlx_pixel_put_to_image(void *img, t_uint x, t_uint y, t_uint color);
void			init_par_mand(t_frac *mand);
int				**init_wintab(void);
void			init_env(t_frac *mand);
t_vec			**init_eqtab(void);
void			free_frac(t_frac *mand, int par);
int				keyhook_f(int keycode, t_frac *mand);
int				mousehook_f(int button, int x, int y, t_frac *mand);
#endif
