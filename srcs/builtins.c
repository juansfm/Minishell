/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:26 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/11/25 14:04:31 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Find out if it's a flag of echo
 * 
 * @param msg string to find out
 * @return int 
 */
static int	ft_echo_flag(char *msg)
{
	int	i;

	i = 0;
	if (!msg)
		return (0);
	if (msg[i] == '-')
		i++;
	else
		return (0);
	while (msg[i] != '\0')
	{
		if (msg[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

/**
 * @brief built-in export
 * 
 * @param g_data general struct
 * @param env_line NAME=VALUE
 */
void	ft_export(t_general *g_data, char **env_line)
{
	t_env	*temp;
	int		i;

	if (!env_line[1])
	{
		ft_print_export(g_data);
		return ;
	}
	i = 1;
	while (env_line[i])
	{
		temp = ft_env_new(env_line[i]);
		if (ft_env_error(temp->name))
		{
			printf("bash: export: '%s': not a valid identifier\n", temp->name);
			ft_free_env(temp);
			return ;
		}
		ft_free_env(temp);
		ft_add_mod_env(g_data, env_line[i]);
		i++;
	}
	return ;
}

/**
 * @brief built-in exit
 * 
 * @param g_data general struct
 */
void	ft_exit(t_general *g_data, char **arg)
{
	int	i;

	(void)g_data;
	if (!arg[1])
		exit(0);
	if (ft_mtxrow(arg) > 2)
	{
		printf("bash: exit: too many arguments\n");
		return ;
	}
	i = -1;
	while (arg[1][++i])
	{
		if ((!ft_isdigit(arg[1][i]) && arg[1][i] != '+' && arg[1][i] != '-')
			|| ((arg[1][i] == '+' || arg[1][i] == '-') && !ft_isdigit(arg[1][i
					+ 1])) || ft_atol(arg[1]) > INT_MAX
			|| ft_atol(arg[0]) < INT_MIN)
		{
			printf("Numeric argument required\n");
			exit(255);
		}
	}
	printf("exit");
	exit(ft_atou(arg[1]) % 256);
}

/**
 * @brief built-in echo
 * 
 * @param g_data general struct
 * @param arg msg to print (with flag)
 */
void	ft_echo(t_general *g_data, char **arg)
{
	int	i;

	(void)g_data;
	if (!arg)
	{
		printf("\n");
		return ;
	}
	i = 1;
	while (ft_echo_flag(arg[i]))
		i++;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!ft_echo_flag(arg[1]))
		printf("\n");
}

/**
 * @brief built-in pwd
 * 
 * @param g_data general struct
 */
void	ft_pwd(t_general *g_data)
{
	char	*pwd;

	(void)g_data;
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
}
