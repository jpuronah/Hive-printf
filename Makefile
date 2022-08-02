# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 08:14:52 by jpuronah          #+#    #+#              #
#    Updated: 2022/08/02 13:55:06 by jpuronah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = libftprintf.a

#FLAGS = -Wall -Wextra -Werror
FLAGS = -Wconversion -Wall -Wextra -Werror# -O2

LIBFT = libft

DIR_S = srcs

DIR_O = obj

HEADER = includes

SOURCES = ft_printf.c \
			parser.c \
			string.c \
			number.c \
			number_base.c \
			number_double_and_float.c \
			write_padding_flags.c \
			get_va_arg_numbers.c \

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@echo "\033[32mlibft compiled \033[0m"
	@mkdir -p obj
	@gcc $(FLAGS) -I includes -o obj/ft_printf.o -c srcs/ft_printf.c
	@mkdir -p obj
	@gcc  $(FLAGS) -I includes -o obj/string.o -c srcs/string.c
	@mkdir -p obj
	@gcc  $(FLAGS) -I includes -o obj/parser.o -c srcs/parser.c
	@mkdir -p obj
	@gcc  $(FLAGS) -I includes -o obj/number.o -c srcs/number.c
	@mkdir -p obj
	@gcc  $(FLAGS) -I includes -o obj/number_double_and_float.o -c srcs/number_double_and_float.c
	@mkdir -p obj
	@gcc  $(FLAGS) -I includes -o obj/write_padding_flags.o -c srcs/write_padding_flags.c
	@mkdir -p obj
	@gcc  $(FLAGS) -I includes -o obj/get_va_arg_numbers.o -c srcs/get_va_arg_numbers.c
	@mkdir -p obj
	@gcc  $(FLAGS) -I includes -o obj/number_base.o -c srcs/number_base.c
	@mkdir -p obj
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[32m Compilation SUCCESS \033[0m"

test:
	@make all
	@echo "\033[32m main & printf linked and runned \033[0m"
	@gcc -o exe main.c libftprintf.a
	./exe

leaks:
	@make all
	@echo "\033[32m main & printf linked and runned \033[0m"
	@gcc -o exe main.c libftprintf.a
	leaks -atExit -- ./exe

nf:
	@mkdir -p obj
	@gcc  -I includes -o obj/ft_printf.o -c srcs/ft_printf.c
	@mkdir -p obj
	@gcc  -I includes -o obj/string.o -c srcs/string.c
	@mkdir -p obj
	@gcc -I includes -o obj/parser.o -c srcs/parser.c
	@mkdir -p obj
	@gcc -I includes -o obj/number.o -c srcs/number.c
	@mkdir -p obj
	@gcc -I includes -o obj/number_double_and_float.o -c srcs/number_double_and_float.c
	@mkdir -p obj
	@gcc -I includes -o obj/write_padding_flags.o -c srcs/write_padding_flags.c
	@mkdir -p obj
	@gcc -I includes -o obj/get_va_arg_numbers.o -c srcs/get_va_arg_numbers.c
	@mkdir -p obj
	@gcc -I includes -o obj/number_base.o -c srcs/number_base.c
	@mkdir -p obj
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[32m Compilation SUCCESS \033[0m"

clean:
	rm -f $(OBJS)
	rm -rf $(DIR_O)
	make clean -C $(LIBFT)
	echo "\033[32m Objects deleted \033[0m"

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)
	echo "\033[32m Everything deleted \033[0m"

re: fclean all

.PHONY: fclean re norme all clean
