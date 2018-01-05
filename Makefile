#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adleau <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 02:34:03 by adleau            #+#    #+#              #
#    Updated: 2018/01/05 13:14:10 by adleau           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC		=	gcc

NAME	=	fractol

LNAME	=	ft

DIR		=	lib$(LNAME)

HDR		=	$(DIR)/$(DIR).a

MDIR	=	mlx

MLX		=	$(MDIR)/lib$(MDIR).a

SRC		=	main.c				\
			free_fractal.c		\
			initializing_stuff.c\
			generic.c			\
			mlx_pixel_put_img.c	\
			fractals.c			\

HEADER	=	includes/general.h	\
			includes/fractal.h 	\
			includes/shortcuts.h\

OBJ		=	$(patsubst %.c,srcs/%.o,$(SRC))

LFLAGS	=	-L$(DIR) -l$(LNAME) -Imlx/ -Lmlx -lmlx -framework OpenGL -framework Appkit

CFLAGS	+=	-Wall -Wextra -Werror -Imlx -Iincludes -Ilibft -I/opt/X11/include

all:	$(HDR) $(MLX) $(NAME)

$(NAME):	$(OBJ) $(HEADER)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)

$(MLX):
	$(MAKE) -C $(MDIR)

$(HDR):
	$(MAKE) -C $(DIR)

clean:
	make -C $(MDIR) clean
	make -C $(DIR) clean
	rm -f $(OBJ) $(HDR)

fclean:		clean
	make -C $(MDIR) clean
	make -C $(DIR) fclean
	rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re
