# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 16:10:59 by jsaavedr          #+#    #+#              #
#    Updated: 2023/10/18 16:57:42 by jsaavedr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c ft_write.c

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

HDR_DIR = ../includes/
HDR = ft_printf.h
HDR_PATH = ${addprefix ${HDR_DIR}, ${HDR}}
HDR_INC = -I ../includes/

all: ${NAME}

${NAME}: ${OBJS} ${HDR_PATH}
	@${CC} -c ${CFLAGS} ${SRCS} ${HDR_INC}
	@ar crs ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re