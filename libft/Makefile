# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obritany <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/05 17:09:06 by obritany          #+#    #+#              #
#    Updated: 2020/11/26 19:38:00 by obritany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
SRCS	=\
		ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_utoa_base.c\
		ft_memccpy.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_strtoupper.c\
		ft_strtolower.c\
		ft_clear.c\
		get_next_line.c
SRCS_B	=\
		ft_lstadd_back.c\
		ft_lstadd_front.c\
		ft_lstclear.c\
		ft_lstdelone.c\
		ft_lstiter.c\
		ft_lstlast.c\
		ft_lstmap.c\
		ft_lstnew.c\
		ft_lstsize.c
OBJS	= $(SRCS:.c=.o)
OBJS_B	= $(SRCS_B:.c=.o)
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

.c.o:
			gcc $(CFLAGS) -c $<

all:		$(NAME)

clean:
			@$(RM) $(OBJS) $(OBJS_B)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

$(NAME):	$(OBJS)
			@ar rcs $(NAME) $(OBJS)

bonus:		$(OBJS) $(OBJS_B)
			@ar rcs $(NAME) $(OBJS) $(OBJS_B)

.PHONY:   all clean fclean re bonus
