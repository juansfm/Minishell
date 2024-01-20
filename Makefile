NAME = minishell

OBJS_DIR = objs/

SRCS = srcs/minishell.c\
		srcs/env.c\
		srcs/env_utils.c\
		srcs/env_print.c\
		srcs/builtins.c\
		srcs/cd.c\
		srcs/env_utils_2.c\
		srcs/cmd.c\
		srcs/multiple_cmd.c\
		srcs/cmd_utils.c

SRCS_PARSER = parser/expansion_utils.c parser/expansion.c parser/lexer_utils.c parser/lexer.c parser/list_cmd.c parser/prompt.c parser/utils_minishell.c parser/utils_parser_cmd.c parser/utils_parser.c parser/utils_parser2.c
#parser/split_modify.c

CFILES = ${SRCS_PARSER} ${SRCS} 

ALL_OBJS = ${addprefix ${OBJS_DIR}, ${CFILES:.c=.o}}

#OBJS = ${addprefix ${OBJS_DIR}, ${SRCS:.c=.o}}

#OBJS_PARSER = ${addprefix ${OBJS_DIR}, ${SRCS_PARSER:.c=.o}}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

RM = rm -rf

LIBFT = libft/libft.a

HDR_DIR = includes/

HDR = minishell.h

HDR_PATH = ${addprefix ${HDR_DIR}, ${HDR}}

HDR_INC = -I ./includes

all: ${NAME}

${NAME}: ${LIBFT} ${ALL_OBJS}
	${CC} ${CFLAGS} ${ALL_OBJS} ${LIBFT} -o ${NAME} -lreadline

${LIBFT}:
	@make -C libft
	
${OBJS_DIR}:
	@mkdir -p ${OBJS_DIR} 

${OBJS_DIR}%.o: %.c ${HDR_PATH}
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} ${HDR_INC} -o $@ -c $<


clean:
	${RM} ${OBJS_DIR}
	${MAKE} -s -C libft/ clean

fclean: clean
	${RM} ${NAME}
	${MAKE} -s -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re