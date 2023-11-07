/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:57:49 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/11/05 16:35:50 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_env
{
	char			*name;
	char			*valor;
	int				equal;
	struct s_env	*next;
}					t_env;

typedef struct s_general
{
	struct s_env	*env;
}					t_general;

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

//BUILTINS
void				ft_export(t_general *g_data, char *env_line);
void				ft_exit(t_general *g_data);
void				ft_echo(t_general *g_data, char *arg);
void				ft_cd(t_general *g_data, char *arg);
void				ft_pwd(t_general *g_data);
void				ft_builtins(t_general *g_data, char *cmd, char *arg);

//CD AUX
void				ft_old_pwd(t_general *g_data);
void				ft_home(t_general *g_data);

void				ft_other_cmd(t_general *g_data, char *cmd, char *arg);

#endif