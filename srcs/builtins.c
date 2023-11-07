/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:26 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/11/05 18:43:35 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_general *g_data, char *env_line)
{
	t_env	*temp;

	if (env_line[0] == '\0')
	{
		ft_print_export(g_data);
		return ;
	}
	temp = ft_env_new(env_line);
	if (ft_env_error(temp->name))
	{
		printf("bash: export: '%s': not a valid identifier\n", temp->name);
		ft_free_env(temp);
		return ;
	}
	ft_free_env(temp);
	ft_add_mod_env(g_data, env_line);
	return ;
}

void	ft_exit(t_general *g_data)
{
	(void)g_data;
	exit(0);
}

void	ft_echo(t_general *g_data, char *arg)
{
	char	**msg;
	int		i;

	(void)g_data;
	if (!arg)
	{
		printf("\n");
		return ;
	}
	msg = ft_split(arg, ' ');
	i = 0;
	while (!ft_strcmp("-n", msg[i]))
		i++;
	while (msg[i])
	{
		ft_putstr_fd(msg[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (ft_strcmp("-n", msg[0]))
		printf("\n");
}

void	ft_pwd(t_general *g_data)
{
	t_env	*pwd;

	pwd = g_data->env;
	while (pwd != NULL)
	{
		if (!ft_strcmp("PWD", pwd->name))
		{
			printf("%s\n", pwd->valor);
			return ;
		}
		pwd = pwd->next;
	}
}

// Los argumentos de esta funcion pueden cambiar segun evoluciona el programa
void	ft_builtins(t_general *g_data, char *cmd, char *arg)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "ECHO"))
		ft_echo(g_data, arg);
	else if (!ft_strcmp(cmd, "cd"))
		ft_cd(g_data, arg);
	else if (!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "PWD"))
		ft_pwd(g_data);
	else if (!ft_strcmp(cmd, "export"))
		ft_export(g_data, arg);
	else if (!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "ENV"))
		ft_print_env(g_data);
	else if (!ft_strcmp(cmd, "unset"))
		ft_delete_env(g_data, arg);
	else if (!ft_strcmp(cmd, "exit"))
		ft_exit(g_data);
	else
		ft_other_cmd(g_data, cmd, arg);
}
