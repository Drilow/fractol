/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 18:59:10 by adleau            #+#    #+#             */
/*   Updated: 2017/12/24 19:58:34 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H
# define WIN_HT 720
# define WIN_WD 1280
# define MAX_IT 100
# include <math.h>
#include <stdio.h>

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
}				t_env;

#endif
