C = clang

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror -O2

LIBFT = libft

DIR_S = srcs

DIR_O = obj

HEADER = includes

SOURCES = ft_printf.c \
			printers.c \
			parser.c \

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@mkdir -p obj
	@gcc $(FLAGS) -I includes -o obj/ft_printf.o -c srcs/ft_printf.c
	@mkdir -p obj
	@gcc  $(FLAGS) -I includes -o obj/printers.o -c srcs/printers.c
	@mkdir -p obj
	@gcc  $(FLAGS) -I includes -o obj/parser.o -c srcs/parser.c
	@mkdir -p obj
	@echo "\033[32mlibft compiled \033[0m"
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[32m Compilation SUCCESS \033[0m"

test:
	@make all
	@echo "\033[32m main & printf linked and runned \033[0m"
	@gcc -o exe main.c libftprintf.a
	./exe


nf:
	@mkdir -p obj
	@gcc  -I includes -o obj/ft_printf.o -c srcs/ft_printf.c
	@mkdir -p obj
	@gcc  -I includes -o obj/printers.o -c srcs/printers.c
	@mkdir -p obj
	@gcc -I includes -o obj/parser.o -c srcs/parser.c
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
