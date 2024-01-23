# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 19:52:34 by jsaavedr          #+#    #+#              #
#    Updated: 2024/01/23 14:06:55 by jsaavedr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
		ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
		ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_free.c ft_mtxrow.c \
		ft_strcmp.c ft_atol.c ft_atou.c ft_strjoin_free.c
SRCS_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
			ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
GNL_SRCS = get_next_line.c get_next_line_utils.c

OBJS_DIR = objs/
SRCS_DIR = srcs/
SRCS_BONUS_DIR = srcs_bonus/
GNL_DIR = get_next_line/

OBJS = ${addprefix ${OBJS_DIR}${SRCS_DIR}, ${SRCS:.c=.o}}
OBJS_BONUS = ${addprefix ${OBJS_DIR}${SRCS_BONUS_DIR}, ${SRCS_BONUS:.c=.o}}
GNL_OBJS = ${addprefix ${OBJS_DIR}${GNL_DIR}, ${GNL_SRCS:.c=.o}}

CC = gcc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -rf

FT_PRINTF = ft_printf/libftprintf.a

HDR_DIR = includes/
HDR = libft.h
HDR_PATH = ${addprefix ${HDR_DIR}, ${HDR}}
HDR_INC = -I ./includes

all: ${NAME}

${NAME}: ${OBJS_DIR}${SRCS_DIR} ${OBJS_DIR}${GNL_DIR} ${OBJS} ${GNL_OBJS} ${FT_PRINTF} ${HDR_PATH}
	ar crs ${NAME} ${OBJS} ${GNL_OBJS} ${FT_PRINTF}

${FT_PRINTF}:
	@make -C ft_printf

${OBJS_DIR}:
	@mkdir -p $@

${OBJS_DIR}${SRCS_DIR}: ${OBJS_DIR}
	@mkdir -p $@

${OBJS_DIR}${SRCS_BONUS_DIR}: ${OBJS_DIR}
	@mkdir -p $@

${OBJS_DIR}${GNL_DIR}: ${OBJS_DIR}
	@mkdir -p $@

${OBJS_DIR}${SRCS_DIR}%.o: ${SRCS_DIR}%.c ${HDR_PATH}
	@${CC} ${CFLAGS} ${HDR_INC} -o $@ -c $<

${OBJS_DIR}${GNL_DIR}%.o: ${GNL_DIR}%.c ${HDR_PATH}
	@${CC} ${CFLAGS} -o $@ -c $<

${OBJS_DIR}${SRCS_BONUS_DIR}%.o: ${SRCS_BONUS_DIR}%.c ${HDR_PATH}
	@${CC} ${CFLAGS} ${HDR_INC} -o $@ -c $<

bonus: ${FT_PRINTF} ${OBJS_DIR}${SRCS_DIR} ${OBJS_DIR}${GNL_DIR} ${OBJS_DIR}${SRCS_BONUS_DIR} ${OBJS} ${GNL_OBJS} ${OBJS_BONUS} ${HDR_PATH}
	@ar crs ${NAME} ${OBJS} ${GNL_OBJS} ${FT_PRINTF} ${OBJS_BONUS}

clean:
	${RM} ${OBJS_DIR}
	${MAKE} -s -C ft_printf/ clean

fclean:		clean
	${RM} ${NAME}
	${MAKE} -s -C ft_printf/ fclean

re:			fclean all

.PHONY: all clean fclean re bonus