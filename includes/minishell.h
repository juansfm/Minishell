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

# define TOKEN_CMD 0
# define TOKEN__ARG 1
# define TOKEN__IN 2
# define TOKEN__OUT 3
# define TOKEN_PIPE 4
# define TOKEN_HERE_DOC_IN 5
# define TOKEN_HERE_DOC_OUT 6

/*  DISPLAY FORMATS:  */
# define RESET          "\e[0m"
# define RED            "\e[31m"
# define GREEN          "\e[32m"
# define YELLOW         "\e[33m"
# define BLUE           "\e[34m"
# define VIOLET         "\e[35m"
# define BACK_RED       "\e[41m"
# define BACK_GREEN     "\e[42m"
# define BACK_YELLOW    "\e[43m"
# define BACK_BLUE      "\e[44m"
# define BACK_VIOLET    "\e[45m"
# define BOLD           "\e[1m"
# define UNDERLINE      "\e[4m"
# define BLINK          "\e[5m"
# define INVERT         "\e[7m"
# define HIDE           "\e[8m"
# define STRIKE         "\e[9m"

int		g_running;
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
	char			*infile_name;
	char			*outfile_name;
	char 			**heredoc; //probando varios heredoc en un solo comando
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_general
{
	char 			*cpy_line;
	char			**split_tokens;
	struct s_env	*env;
	struct s_cmd	*cmd;
	//struct s_token	*token;
	int				og_in;
	int				og_out;
	char 			**array_tokens;
}					t_general;
/*******************************parser estructuras**************************/
/*comillas*/
typedef struct s_process_character
{
    char *token;
    int *j;
    int *k;
    int *in_quotes;
    char *quote_char;
    char *temp;
}              t_process_character;
//tokens
typedef struct s_token
{
	int				type_token;
	int 			len;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_temp //no se usa
{
	char			*temp;
	struct s_temp	*next;
}					t_temp;

/*No lo uso por ahora
*/


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

//HEREDOC
void				ft_heredoc(t_general *g_data, char *delimiter);
void				ft_redir(t_general *g_data, t_cmd *cmd);

//CMD_UTILS
int					ft_cmd_len(t_general *g_data);

//MULTIPLE_CMD
void				ft_multiple_cmd(t_general *g_data, t_cmd *cmd);


//************************minishell.c********************************
void				ft_minish(char **envp);
int 				main(int argc, char **argv, char **envp);
void 				ft_print_commands(t_cmd *cmd);
void ft_quita_comillas(t_general *g_data);

//***********************ft_expansion_utils.c***********************
char				*ft_extract_word(char *str, int pos_dolar, int *pos);
int 				ft_encontrar_dolar(char *cadena, int inicio);//funciona
char 				*ft_cpy_part(char *str, int *pos, int num_chars);
char 				*ft_remodelar_cadena(char *split_tokens, char *palabra_dolar, char *word_exchange, int pos_dolar);

//**************************expansion.c********************************
void 				ft_vamos_a_expandir(t_general *g_data); //nueva funcion 16/01/2024
char 				*ft_funcion_que_lo_lleva_todo(t_general *g_data, char *cmd);

//**********************************lexer_utils.c**********************************
int 				ft_count_pipes(char **input);
char				*ft_concatenate_strings(char *temp, char *input);
char 				**ft_concatenate_until_pipe(char **input);

//**********************lexer.c********************************
void				ft_parse_tokens(t_general *g_data);
void 				ft_funcion_junta_redirecciones(t_general *g_data);
void				ft_parser(t_general *g_data, char *line);

//**********************list_cmd.c********************************
t_cmd				*ft_cmd_last(t_general *g_data);
void				ft_cmd_add_back(t_general *g_data, t_cmd *new);
t_cmd				*ft_init_cmd(void);
t_cmd				*ft_cmd_new(char *arg);
void				ft_cmd_lst(t_general *g_data, char **mtx);//este es el de juan

//*************************prompt.c********************************
void				ft_prompt(void);

//**************************utils_minishell.c**************************
t_cmd 				*ft_create_new_cmd(void);
void 				ft_generate_cmds_from_tokens(t_general *g_data);

//**************************utils_parsers_cmd.c**************************
void 				ft_process_args(t_cmd *cmd, char **mtx);
void 				ft_fill_cmd(t_cmd *cmd, char **mtx);
void 				ft_process_input(t_cmd *cmd, char **mtx, int *i);
void 				ft_process_output(t_cmd *cmd, char **mtx, int *i, int append);
void				ft_free_cmd(t_general *g_data);

//*************************utils_parser.c********************************
int 				ft_char_reserved(char c);
int 				ft_isspace(int c);
void 				ft_process_quote(t_general *g_data, int *pos);
void				ft_restore_quotes(char **split_tokens);
void				*ft_realloc(void *ptr, size_t size, size_t new_size);

//*************************utils_parser2.c********************************
char				*ft_extract_token(char *cpy_line, int start, int end);
char 				**ft_tokenize(t_general *g_data, int len);
int					ft_contar_cadenas_validas(char **cadena_de_cadenas);
char 				**ft_eliminar_espacios(char **cadena_de_cadenas);

//***************************comillas.c**********************************
//char *process_token(t_process_character *p);
//void replace_token_in_cmd(t_general *g_data, int i, char *temp);
//void ft_quita_comillas(t_general *g_data);
//cosas.c//no se usa
t_cmd *ft_split_commands_by_pipe(char **tokens);
void ft_add_token_to_cmd(t_cmd *current_cmd, char *token, t_temp *temp);
void ft_print_tokens(t_token *head);
int ft_get_token_type(char *value);
t_token *ft_new_token(char *value);
t_token *ft_convert_to_tokens(char **str);




#endif