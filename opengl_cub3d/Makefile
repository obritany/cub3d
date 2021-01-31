#SETUP
NAME		= cub3D
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
CFLAGS_APP	= -framework OpenGL -framework AppKit
RM			= rm -f

#FILES
FLS			= cub3d.c\
			parse.c\
			parse_map.c\
			parse_tools.c\
			parse_check.c\
			gnl.c\
			key.c\
			screen.c\
			screen_col.c\
			sprite.c\
			bitmap.c\
			tools.c

SRCS_DIR	= sources/
SRCS		= $(addprefix $(SRCS_DIR), $(FLS))
OBJS		= $(SRCS:.c=.o)

MLX_DIR		= mlx_opengl/
MLX			= libmlx.a

#COMMANDS
all:		$(NAME)

$(NAME):	$(MLX) $(OBJS)
			$(CC) $(CFLAGS) $(CFLAGS_APP) $(MLX) $(OBJS) -o $(NAME)

$(MLX):
			$(MAKE) -C $(MLX_DIR)
			mv $(MLX_DIR)$(MLX) $(MLX)

clean:
			$(RM) $(OBJS)
			$(MAKE) -C $(MLX_DIR) clean
			$(RM) bitmap.bmp

fclean:		clean
			$(RM) $(NAME)
#			$(RM) $(MLX)

re:			fclean all

.PHONY:		all clean fclean re
