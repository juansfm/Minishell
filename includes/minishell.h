#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
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
# define RESET "\e[0m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define VIOLET "\e[35m"
# define BACK_RED "\e[41m"
# define BACK_GREEN "\e[42m"
# define BACK_YELLOW "\e[43m"
# define BACK_BLUE "\e[44m"
# define BACK_VIOLET "\e[45m"
# define BOLD "\e[1m"
# define UNDERLINE "\e[4m"
# define BLINK "\e[5m"
# define INVERT "\e[7m"
# define HIDE "\e[8m"
# define STRIKE "\e[9m"

int					g_running;
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
	char			**heredoc;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_general
{
	char			*cpy_line;
	char			**split_tokens;
	struct s_env	*env;
	struct s_cmd	*cmd;
	int				og_in;
	int				og_out;
	int				status;
}					t_general;
/*******************************parser estructuras**************************/
/*comillas*/

typedef struct s_process_data
{
	t_general		*g_data;
	int				i;
	int				j;
	int				k;
	int				in_quotes;
	char			quote_char;
	char			*temp;
}					t_process_data;

typedef struct s_cmd_data
{
	int				i;
	int				j;
	int				k;
	int				len;
	int				lenh;
}					t_cmd_data;


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
int					ft_export(t_general *g_data, char **env_line);
void				ft_exit(t_general *g_data, char **arg);
void				ft_echo(t_general *g_data, char **arg);
int					ft_cd(t_general *g_data, char **arg);
void				ft_pwd(t_general *g_data);
int					ft_builtins(t_general *g_data, char **arg);

//CD AUX
int					ft_old_pwd(t_general *g_data);
int					ft_home(t_general *g_data);
int					ft_other_cd(t_general *g_data, char *dir, char **arg);

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
int					main(int argc, char **argv, char **envp);

//***********************ft_expansion_utils.c***********************
char				*ft_extract_word(char *str, int pos_dolar, int *pos);
int					ft_encontrar_dolar(char *cadena, int inicio);
char				*ft_cpy_part(char *str, int *pos, int num_chars);
char				*ft_remodelar_cadena(char *split_tokens,
						char *palabra_dolar, char *word_exchange,
						int pos_dolar);

//**************************expansion.c********************************
void				ft_vamos_a_expandir(t_general *g_data);
char				*ft_expand_all(t_general *g_data, char *cmd);
char				*ft_get_word_exchange(t_general *g_data,
						char *palabra_dolar);
char				*ft_process_dolar(t_general *g_data, char *string_restruc,
						int pos_dolar, int *pos);

//**********************************lexer_utils.c**********************
int					ft_count_pipes(char **input);
char				*ft_concatenate_strings(char *temp, char *input);
char				**ft_concatenate_until_pipe(char **input);

//**********************lexer.c********************************
void				ft_parse_tokens(t_general *g_data);
void				ft_funcion_junta_redirecciones(t_general *g_data);
void				ft_parser(t_general *g_data, char *line);
int					ft_solo_espacios(char *line);

//**********************list_cmd.c********************************
t_cmd				*ft_cmd_last(t_general *g_data);
void				ft_cmd_add_back(t_general *g_data, t_cmd *new);
t_cmd				*ft_init_cmd(void);
void				ft_cmd_lst(t_general *g_data, char **mtx);

//*************************prompt.c********************************
void				ft_prompt(void);

//***************************signals.c*******************************
void				ft_handler(int sig);
void				ft_ctrl_d(t_general *g_data);
//**************************utils_minishell.c**************************
t_cmd				*ft_create_new_cmd(void);
void				ft_generate_cmds_from_tokens(t_general *g_data);
void				ft_quita_comillas(t_general *g_data);
void				ft_print_commands(t_cmd *cmd);

//**************************utils_parsers_cmd.c**************************
void				ft_process_args(t_cmd *cmd, char **mtx);
void				ft_fill_cmd(t_cmd *cmd, char **mtx);
void				ft_process_input(t_cmd *cmd, char **mtx, int *i);
void				ft_process_output(t_cmd *cmd, char **mtx, int *i,
						int append);
void				ft_free_cmd(t_general *g_data);

//*************************utils_parser.c********************************
int					ft_char_reserved(char c);
int					ft_isspace(int c);
void				ft_process_quote(t_general *g_data, int *pos);
void				ft_replace_special_chars(t_general *g_data, int *pos,
						char current_char, int *count_quotes);
void				ft_restore_quotes(char **split_tokens);

//*************************utils_parser2.c********************************
char				*ft_extract_token(char *cpy_line, int start, int end);
char				**ft_tokenize(t_general *g_data);
int					ft_contar_cadenas_validas(char **cadena_de_cadenas);
char				**ft_eliminar_espacios(char **cadena_de_cadenas);

//***************************comillas.c**********************************
void				ft_process_quote_character(t_process_data *p);
void				ft_process_non_quote_character(t_process_data *p);
void				ft_process_token(t_process_data *p);
void				ft_replace_token_in_cmd(t_process_data *p);

//***************************nueva_funcion_new.c****************************
void				ft_process_input_file(t_cmd *cmd, char **mtx,
						t_cmd_data *data);
void				ft_process_output_file(t_cmd *cmd, char **mtx,
						t_cmd_data *data);
void				ft_process_redirects(t_cmd *cmd, char **mtx,
						t_cmd_data *data);
void				ft_fill_cmd_and_heredoc(t_cmd *cmd, char **mtx,
						t_cmd_data *data);
t_cmd				*ft_cmd_new(char *arg);

#endif