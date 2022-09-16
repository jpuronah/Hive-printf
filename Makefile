# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 08:14:52 by jpuronah          #+#    #+#              #
#    Updated: 2022/08/09 11:55:40 by jpuronah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror
#FLAGS = -Wconversion -Wall -Wextra -Werror# -O2
AR = ar rcs

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

$(DIR_O)ARRC = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@echo "\033[32m libft compiled \033[0m"
	@mkdir -p $(DIR_O)
	



	@mkdir -p $(DIR_O)
	@gcc $(FLAGS) -I includes -o $(DIR_O)/ft_printf.o -c $(DIR_S)/ft_printf.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/string.o -c $(DIR_S)/string.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/parser.o -c $(DIR_S)/parser.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/number.o -c $(DIR_S)/number.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/number_double_and_float.o -c $(DIR_S)/number_double_and_float.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/write_padding_flags.o -c $(DIR_S)/write_padding_flags.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/get_va_arg_numbers.o -c $(DIR_S)/get_va_arg_numbers.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/number_base.o -c $(DIR_S)/number_base.c
	@mkdir -p $(DIR_O)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $($(DIR_O)ARRC)
	@ranlib $(NAME)
	@echo "\033[32m ft_printf Compilation SUCCESS \033[0m"

test:
	@make all
	@echo "\033[32m main & printf linked and runned \033[0m"
	@gcc -o test_exe main.c libftprintf.a
	./test_exe

leaks:
	@make leaks -C $(LIBFT)
	@echo "\033[32mlibft compiled \033[0m"
	@mkdir -p $(DIR_O)
	@gcc $(FLAGS) -I includes -o $(DIR_O)/ft_printf.o -c $(DIR_S)/ft_printf.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/string.o -c $(DIR_S)/string.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/parser.o -c $(DIR_S)/parser.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/number.o -c $(DIR_S)/number.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/number_double_and_float.o -c $(DIR_S)/number_double_and_float.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/write_padding_flags.o -c $(DIR_S)/write_padding_flags.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/get_va_arg_numbers.o -c $(DIR_S)/get_va_arg_numbers.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/number_base.o -c $(DIR_S)/number_base.c
	@mkdir -p $(DIR_O)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $($(DIR_O)ARRC)
	@ranlib $(NAME)
	@echo "\033[32m Compilation SUCCESS \033[0m"
	@echo "\033[32m main & printf linked and runned \033[0m"
	@gcc -o test_exe main.c libftprintf.a
	leaks -atExit -- ./test_exe

nf:
	@mkdir -p $(DIR_O)
	@gcc  -I includes -o $(DIR_O)/ft_printf.o -c $(DIR_S)/ft_printf.c
	@mkdir -p $(DIR_O)
	@gcc  -I includes -o $(DIR_O)/string.o -c $(DIR_S)/string.c
	@mkdir -p $(DIR_O)
	@gcc -I includes -o $(DIR_O)/parser.o -c $(DIR_S)/parser.c
	@mkdir -p $(DIR_O)
	@gcc -I includes -o $(DIR_O)/number.o -c $(DIR_S)/number.c
	@mkdir -p $(DIR_O)
	@gcc -I includes -o $(DIR_O)/number_double_and_float.o -c $(DIR_S)/number_double_and_float.c
	@mkdir -p $(DIR_O)
	@gcc -I includes -o $(DIR_O)/write_padding_flags.o -c $(DIR_S)/write_padding_flags.c
	@mkdir -p $(DIR_O)
	@gcc -I includes -o $(DIR_O)/get_va_arg_numbers.o -c $(DIR_S)/get_va_arg_numbers.c
	@mkdir -p $(DIR_O)
	@gcc -I includes -o $(DIR_O)/number_base.o -c $(DIR_S)/number_base.c
	@mkdir -p $(DIR_O)
	@cp libft/libft.a ./$(NAME)
	@$(AR) $(NAME) $($(DIR_O)ARRC)
	@ranlib $(NAME)
	@echo "\033[32m Compilation SUCCESS  ---  NO FLAGS \033[0m"

clean:
	@make clean -C $(LIBFT)
	@rm -f $($(DIR_O)ARRC)
	@rm -rf $(DIR_O)
	@echo "\033[32m ft_printf object files cleaned \033[0m"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@echo "\033[32m Everything cleaned \033[0m"

cleantest:
	rm -f $($(DIR_O)S)
	rm -rf $(DIR_O)
	rm -f test_exe
	make clean -C $(LIBFT)
	echo "\033[32m objects deleted \033[0m"

re: fclean all

.PHONY: re norme all clean fclean cleantest nf
