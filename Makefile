# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 11:47:34 by iblanco-          #+#    #+#              #
#    Updated: 2024/06/10 11:50:09 by iblanco-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc -Wall -Werror -Wextra -fsanitize=address -g3

RM = rm -f

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT) clean

fclean:	clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean

limpito: all clean

re:	fclean all

.PHONY:	all clean fclean re