# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkarlon- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/26 14:51:25 by lkarlon-          #+#    #+#              #
#    Updated: 2019/04/13 17:40:19 by lkarlon-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =		./srcs/fdf.c \
			./get_color.c
INCLUDES =	./includes/libft.h \
			./minilibx_macos/mlx.h \
			./fdf_prms.h
OBJ =		$(SRCS:%.c = %.o)
CC =		gcc
FLAGS =		-Wall -Wextra -Werror -c

all:	$(NAME)

$(NAME): $(OBJ)
				@ar rc $(NAME) $(OBJ)
				@ranlib $(NAME)

%.o: %.c $(INCLUDES)
				@$(CC) $(FLAGS) -c $< -o $@

clean:
				@rm -f $(OBJ)

fclean: clean	
				@rm -f $(NAME)

re: fclean all