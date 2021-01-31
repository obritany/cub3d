# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obritany <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/27 17:37:57 by obritany          #+#    #+#              #
#    Updated: 2021/01/27 17:37:59 by obritany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP
NAME		= cub3d
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
CFLAGS_APP	= -framework OpenGL -framework Appkit
RM			= rm -f

#FILES
SRCS		= main.c\
			ft_check_map.c\
			ft_parse_map.c\
			ft_cub_cl_tex_for_parse.c\
			ft_parse_param.c\
			ft_cub_parse.c\
			ft_cub_parse_utils.c\
			ft_cub_resolution_for_parse.c\
			ft_init_mlx.c\
			ft_raycasting.c\
			ft_rgbt.c\
			ft_drawing.c\
			ft_controller_player.c\
			ft_controller.c\
			ft_bmp_screen.c\
			ft_init_mlx_utils.c\
			ft_drawing_sprites.c\
			ft_raycasting_utils.c
			
OBJS 		= $(SRCS:.c=.o)

MLX_DIR		= mlx_mms/
MLX			= libmlx.dylib

LIBFT_DIR	= libft/
LIBFT		= libft.a

#COMMANDS
all:		$(NAME)

$(NAME):	$(LIBFT) $(MLX) $(OBJS)
			mv $(LIBFT_DIR)$(LIBFT) $(LIBFT)
			mv $(MLX_DIR)$(MLX) $(MLX)
			$(CC) $(CFLAGS) $(CFLAGS_APP) $(LIBFT) $(MLX) $(OBJS) -o $(NAME)

$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)

$(MLX):
			$(MAKE) -C $(MLX_DIR)

clean:
			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFT_DIR) clean
			$(MAKE) -C $(MLX_DIR) clean
			$(RM) ./Screenshot.bmp

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(LIBFT)
			$(RM) $(MLX)

re:			fclean all

.PHONY:		all clean fclean re
