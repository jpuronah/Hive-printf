# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 15:40:47 by jpuronah          #+#    #+#              #
#    Updated: 2022/08/04 13:18:25 by jpuronah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
#CFLAGS = -Wconversion -Wall -Wextra -Werror# -O2
AR = ar rcs
LIBFT = libft
HEADER = includes
SOURCES = ./ft_atoi \
			./ft_bzero \
			./ft_isalnum \
			./ft_isalpha \
			./ft_isascii \
			./ft_isdigit \
			./ft_isprint \
			./ft_itoa \
			./ft_lstadd \
			./ft_lstat \
			./ft_lstdel \
			./ft_lstcount \
			./ft_lstdelone \
			./ft_lstiter \
			./ft_lstmap \
			./ft_lstnew \
			./ft_memalloc \
			./ft_memccpy \
			./ft_memchr \
			./ft_memcmp \
			./ft_memcpy \
			./ft_memdel \
			./ft_memmove \
			./ft_memset \
			./ft_putchar \
			./ft_putchar_fd \
			./ft_putendl \
			./ft_putendl_fd \
			./ft_putnbr \
			./ft_putnbr_fd \
			./ft_putstr \
			./ft_putstr_fd \
			./ft_strcat \
			./ft_strchr \
			./ft_strclr \
			./ft_strcmp \
			./ft_strcpy \
			./ft_strdel \
			./ft_strdup \
			./ft_strequ \
			./ft_striter \
			./ft_striteri \
			./ft_strjoin \
			./ft_strlcat \
			./ft_strlen \
			./ft_strmap \
			./ft_strmapi \
			./ft_strncat \
			./ft_strncmp \
			./ft_strncpy \
			./ft_strnequ \
			./ft_strnew \
			./ft_strnstr \
			./ft_strrchr \
			./ft_strsplit \
			./ft_strstr \
			./ft_strsub \
			./ft_strtrim \
			./ft_tolower \
			./ft_toupper \
			./get_next_line \
			./ft_countwords \
			./ft_lstrev \
			./ft_abs \
			./ft_create_elem \
			./ft_max \
			./ft_max_double \
			./ft_abs_db \
			./ft_pow \
			./ft_islower \
			./ft_isupper \
			./ft_min \
			./ft_strchri \
			./ft_abs_long_long

#SRCS = $(addprefix $(-), $(addsuffix .c, $(SOURCES)))
#OBJS = $(addsuffix .o, $(DIR_O)/$(SOURCES))
#mkdir -p $(DIR_O)
#MKDIR_O = mkdir -p $(DIR_O)
OBJS = $(addprefix $(-), $(addsuffix .o, $(SOURCES)))

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

all: $(NAME)

clean:
	@rm -f *.o
#	@echo "\033[32m libft object files deleted \033[0m"

fclean: clean
	rm -f libft.a

re: fclean all

.PHONY: all fclean clean re
