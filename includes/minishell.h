#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define TOKEN_WORD 0
# define TOKEN_PIPE 1
# define TOKEN_REDIR_IN 2
# define TOKEN_REDIR_OUT 3
# define TOKEN_DOLLAR 4
# define TOKEN_HERE_DOC_IN 5
# define TOKEN_HERE_DOC_OUT 6

typedef struct s_env
{
	char			*name;
	char			*valor;
	int				equal;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			**cmd;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_general
{
	char 			*cpy_line;
	//char			**split_tokens;
	struct s_env	*env;
	struct s_cmd	*cmd;
	struct s_token	*token;
}					t_general;

typedef struct s_token
{
	int				type_token;
	int 			len;
	char			*value;
	struct s_token	*next;
}					t_token;

// t_general			g_data;

//ENV
void				ft_dup_env(t_general *g_data, char **envp);
void				ft_add_mod_env(t_general *g_data, char *env_new);
void				ft_delete_env(t_general *g_data, char *env_del);
int					ft_env_error(char *env_line);

void				ft_print_env(t_general *g_data);
void				ft_print_export(t_general *g_data);

//ENV_UTILS
void				ft_env_add_back(t_general *g_data, t_env *new);
t_env				*ft_env_last(t_general *g_data);
t_env				*ft_env_new(char *env_line);
void				ft_free_env(t_env *env);
char				**ft_env_split(char *line, char c);
t_env				*ft_env_search(t_general *g_data, char *name);
int					ft_env_len(t_general *g_data);

//BUILTINS
void				ft_export(t_general *g_data, char **env_line);
void				ft_exit(t_general *g_data, char **arg);
void				ft_echo(t_general *g_data, char **arg);
void				ft_cd(t_general *g_data, char **arg);
void				ft_pwd(t_general *g_data);
int					ft_builtins(t_general *g_data, char **arg);

//CD AUX
void				ft_old_pwd(t_general *g_data);
void				ft_home(t_general *g_data);

//CMD
int					ft_other_cmd(t_general *g_data, char **arg);
char				**ft_union_cmd_arg(char *cmd, char **arg);
char				**ft_env_mtx(t_general *g_data);
char				*ft_path(t_general *g_data, char *cmd);

//CMD_UTILS
int					ft_cmd_len(t_general *g_data);

//MULTIPLE_CMD
void				ft_multiple_cmd(t_general *g_data, t_cmd *cmd);


//minishell start
void				ft_minish(char **envp);
int 				main(int argc, char **argv, char **envp);
t_cmd				*ft_cmd_new(char *arg);
void				ft_cmd_add_back(t_general *g_data, t_cmd *new);
t_cmd				*ft_cmd_last(t_general *g_data);
void				ft_free_cmd(t_general *g_data);
void				ft_cmd_lst(t_general *g_data, char **mtx);
t_cmd				*ft_cmd_new(char *arg);
void				ft_cmd_add_back(t_general *g_data, t_cmd *new);

//lexer

int					ft_process_quote_content_double(char *line, int len, int pos, t_token **head);
int					ft_process_quote_content_sim(char *line, int len, int pos, t_token **head);
int					ft_process_word(char *line, int len, int pos, t_token **head);

void				ft_parse_tokens(t_general *g_data);
void				ft_parser(t_general *g_data, char *line);
//void	ft_process_word(char *line, int len, int pos, t_token **head);

//list_tokens

t_token 			*ft_new_token(int type_token, char *value);
void 				ft_add_token_in_general(t_token **head, int type, char *value);
//void 				ft_free_tokens(t_token *head);

//lexer_utils

void 				ft_print_tokens(t_token *head);
int 				ft_char_reserved(char c);
void 				ft_process_quote(t_general *g_data, int *pos);
//void				ft_process_red_in_quote(t_general *g_data, int *pos);nuevo no valido
//void				ft_process_pipe_in_quote(t_general *g_data, int *pos);nuevo no valido
void				ft_restore_quotes(char **split_tokens);
char				*ft_extract_token(char *cpy_line, int start, int end);
char 				**ft_tokenize(t_general *g_data, int len);
//void 				ft_free_tokens(char **split_tokens);
int 				ft_isspace(int c);


//split_modify.c
//char				**ft_split_modify(char *str, char c, char **matrix);

//lexer_utils2
//tengo que cambiarle los nombres a estas funciones
//int 				ft_espacio_antes(char *cadena, int pos_caracter);
//int 				ft_espacio_despues(char *cadena, int *len, int pos_caracter);
//int 				ft_change_len(int *espacios_ad, int *len);
//char 				*ft_agregar_espacios(char *cadena, int *len, int pos_caracter, int *espacios_ad);
//void 				ft_modificar_cadena(t_general *g_data, int *pos_caracter);

//parset_utils2


#endif