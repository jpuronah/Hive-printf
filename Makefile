C = clang

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror -O2

LIBFT = libft

DIR_S = srcs

DIR_O = obj

HEADER = includes

SOURCES = ft_printf.c \
			itoa_double.c \
			init_set_update_flags.c \
			printers.c \

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME):
	mkdir -p obj
	cc  -I includes -o obj/ft_printf.o -c srcs/ft_printf.c
	mkdir -p obj
	cc  -I includes -o obj/init_set_update_flags.o -c srcs/init_set_update_flags.c
	mkdir -p obj
	cc  -I includes -o obj/itoa_double.o -c srcs/itoa_double.c
	mkdir -p obj
	cc  -I includes -o obj/printers.o -c srcs/printers.c
	mkdir -p obj
	make -C $(LIBFT)
	cp libft/libft.a ./$(NAME)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

test:
	@make all
	@gcc -o exe main.c libftprintf.a
	./exe

clean:
	rm -f $(OBJS)
	rm -rf $(DIR_O)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: fclean re norme all clean
