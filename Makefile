# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 08:14:52 by jpuronah          #+#    #+#              #
#    Updated: 2022/10/18 10:55:03 by jpuronah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror
AR = ar rcs
LIBFT = libft
DIR_S = srcs
DIR_O = obj
HEADER = includes
SOURCES = ft_printf.c \
			parse.c \
			print_string.c \
			print_number.c \
			print_number_base.c \
			print_float.c \
			print_float_helpers.c \
			padding_and_pfwrite.c \
			get_va_arg_numbers.c \
			helpers.c

$(DIR_O) = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@echo "libft compiled"
	@mkdir -p $(DIR_O)
	@gcc $(FLAGS) -I includes -o $(DIR_O)/ft_printf.o -c $(DIR_S)/ft_printf.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/print_string.o -c $(DIR_S)/print_string.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/parse.o -c $(DIR_S)/parse.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/print_number.o -c $(DIR_S)/print_number.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/print_float.o -c $(DIR_S)/print_float.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/print_float_helpers.o -c $(DIR_S)/print_float_helpers.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/padding_and_pfwrite.o -c $(DIR_S)/padding_and_pfwrite.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/get_va_arg_numbers.o -c $(DIR_S)/get_va_arg_numbers.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/print_number_base.o -c $(DIR_S)/print_number_base.c
	@mkdir -p $(DIR_O)
	@gcc  $(FLAGS) -I includes -o $(DIR_O)/helpers.o -c $(DIR_S)/helpers.c
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $($(DIR_O))
	@ranlib $(NAME)
	@echo "ft_printf COMPILED"

lib:
	@make -C $(LIBFT)

clean:
	@make clean -C $(LIBFT)
	@rm -f $($(DIR_O))
	@rm -rf $(DIR_O)

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME)

re: fclean all
