/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:57:49 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/10/22 19:27:43 by jsaavedr         ###   ########.fr       */
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

t_general			g_data;

//ENV
void				ft_dup_env(char **envp);
void				ft_add_mod_env(char *env_new);
void				ft_delete_env(char *env_del);
int					ft_env_error(char *env_line);

void				ft_print_env(void);
void				ft_print_export(void);

//ENV_UTILS
void				ft_env_add_back(t_env *new);
t_env				*ft_env_last(void);
t_env				*ft_env_new(char *env_line);
void				ft_free_env(t_env *env);
char				**ft_env_split(char *line);

#endif