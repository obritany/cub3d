#SETUP
NAME		= cub3d
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
CFLAGS_APP	= -framework OpenGL -framework AppKit
RM			= rm -f

#FILES
FLS			= add_sprites.c\
			control.c\
			cub3d.c\
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

MLX_DIR		= mlx_opengl/
MLX			= libmlx.a

LIBFT_DIR	= libft/
LIBFT		= libft.a

#COMMANDS
all:		$(NAME)

$(NAME):	$(MLX) $(LIBFT) $(OBJS)
			$(CC) $(CFLAGS) $(CFLAGS_APP) $(MLX) $(LIBFT) $(OBJS) -o $(NAME)
# 			./cub3d maps/map_mode.cub

$(MLX):
			$(MAKE) -C $(MLX_DIR)
			mv $(MLX_DIR)$(MLX) $(MLX)

$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)
			mv $(LIBFT_DIR)$(LIBFT) $(LIBFT)

clean:
# 			$(RM) $(OBJS)
# 			$(MAKE) -C $(MLX_DIR) clean
# 			$(MAKE) -C $(LIBFT_DIR) clean
# 			$(RM) bitmap.bmp

fclean:		clean
# 			$(RM) $(NAME)
#			$(RM) $(MLX)
#			$(RM) $(LIBFT)

re:			fclean all

.PHONY:		all clean fclean re
