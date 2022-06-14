# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 14:52:31 by jpuronah          #+#    #+#              #
#    Updated: 2022/06/14 14:55:16 by jpuronah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf
SOURCES = ft_printf.c
OBJECTIVES = $(SOURCES:.c=.o)
LIBFT = ./libft_fdf/
CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	gcc -c $(CFLAGS) $(SOURCES)
	gcc $(OBJECTIVES) $(CFLAGS) -o $(NAME)
clean:
	/bin/rm -f $(OBJECTIVES)
	make -C $(LIBFT) clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIBFT) fclean

re: fclean all