# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/15 17:19:28 by jpuronah          #+#    #+#              #
#    Updated: 2022/06/15 20:34:33 by jpuronah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf
SOURCES = ft_printf.c itoa_double.c
OBJECTIVES = $(SOURCES:.c=.o)
FLAGS = -Wconversion -Wall -Wextra -Werror
LIBFT = ./libft/
LIBFT_A = ./libft/libft.a

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	gcc -c $(CFLAGS) $(SOURCES)
	gcc $(OBJECTIVES) $(CFLAGS) -o $(NAME) $(LIBFT_A)

nf: 
	gcc -c $(SOURCES)
	gcc $(OBJECTIVES) -o $(NAME) $(LIBFT_A)

clean:
	/bin/rm -f $(OBJECTIVES)
	make -C $(LIBFT) clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIBFT) fclean

re: fclean all
