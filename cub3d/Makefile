# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obritany <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/06 17:26:00 by obritany          #+#    #+#              #
#    Updated: 2021/03/06 17:26:03 by obritany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP
NAME		= cub3d
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
CFLAGS_APP	= -framework OpenGL -framework AppKit
RM			= rm -f

#FILES
FLS			= cub3d.c\
            add_sprites.c\
			control.c\
			draw_column.c\
			draw_image.c\
			parse_map.c\
			parser.c\
			read_map_file.c\
			save_bmp.c\
			utils.c

SRCS_DIR	= sources/
SRCS		= $(addprefix $(SRCS_DIR), $(FLS))
OBJS		= $(SRCS:.c=.o)

MLX_DIR		= libmlx/
MLX			= $(MLX_DIR)libmlx.a

LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)libft.a

#COMMANDS
all:		$(NAME)

$(NAME):	$(MLX) $(LIBFT) $(OBJS)
			$(CC) $(CFLAGS) $(CFLAGS_APP) $(MLX) $(LIBFT) $(OBJS) -o $(NAME)

$(MLX):
			$(MAKE) -C $(MLX_DIR)

$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)

clean:
			$(RM) $(OBJS)
			$(MAKE) -C $(MLX_DIR) clean
			$(MAKE) -C $(LIBFT_DIR) clean
			$(RM) screen.bmp

fclean:		clean
			$(RM) $(NAME)
			@$(RM) $(MLX)
			@$(RM) $(LIBFT)
			@echo Project cleaned!

re:			fclean all

.PHONY:		all clean fclean re
