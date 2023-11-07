# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/15 18:18:12 by jsaavedr          #+#    #+#              #
#    Updated: 2023/11/05 16:35:14 by jsaavedr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

SRCS_DIR = srcs/
OBJS_DIR = objs/

SRCS = minishell.c env.c env_utils.c env_print.c builtins.c cd.c env_utils_2.c cmd.c
OBJS = ${addprefix ${OBJS_DIR}${SRCS_DIR}, ${SRCS:.c=.o}}


CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
RM = rm -rf

LIBFT = libft/libft.a

HDR_DIR = includes/
HDR = minishell.h
HDR_PATH = ${addprefix ${HDR_DIR}, ${HDR}}
HDR_INC = -I ./includes

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS_DIR}${SRCS_DIR} ${OBJS} ${HDR_PATH}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME} -lreadline

${LIBFT}:
	@make -C libft
	
${OBJS_DIR}:
	@mkdir $@

${OBJS_DIR}${SRCS_DIR}: ${OBJS_DIR}
	@mkdir $@

${OBJS_DIR}${SRCS_DIR}%.o: ${SRCS_DIR}%.c ${HDR_PATH}
	@${CC} ${CFLAGS} ${HDR_INC} -o $@ -c $<

clean:
	${RM} ${OBJS_DIR}
	${MAKE} -s -C libft/ clean

fclean: clean
	${RM} ${NAME}
	${MAKE} -s -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re