# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jzuazo <jzuazo@student.42urduliz.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/28 13:53:27 by jzuazo            #+#    #+#              #
#    Updated: 2026/10/24 14:17:12 by jzuazo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
AR = ar rcs
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SOURCE_FILES = ft_printf.c ft_print_char.c ft_print_str.c ft_print_nbr.c \
		ft_print_hex.c

OBJECTS = ${SOURCE_FILES:.c=.o}

%.o: %.c ft_printf.h
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJECTS}
		${AR} ${NAME} ${OBJECTS}

all: ${NAME}

clean:
	${RM} ${OBJECTS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re