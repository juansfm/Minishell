/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:28:19 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/11/03 19:05:34 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup_env(t_general *g_data, char **envp)
{
	t_env	*node;
	int		i;

	i = -1;
	while (envp[++i])
	{
		node = ft_env_new(envp[i]);
		ft_env_add_back(g_data, node);
	}
}

void	ft_add_mod_env(t_general *g_data, char *env_new)
{
	t_env	*temp;
	t_env	*new;

	temp = g_data->env;
	new = ft_env_new(env_new);
	while (temp != NULL)
	{
		if (!ft_strcmp(temp->name, new->name))
		{
			if (!ft_strchr(env_new, '='))
			{
				ft_free_env(new);
				return ;
			}
			free(temp->valor);
			temp->valor = ft_strdup(new->valor);
			ft_free_env(new);
			return ;
		}
		temp = temp->next;
	}
	ft_env_add_back(g_data, new);
}

void	ft_delete_env(t_general *g_data, char *env_del)
{
	t_env	*first;
	t_env	*second;

	first = g_data->env;
	if (!ft_strcmp(first->name, env_del))
	{
		g_data->env = g_data->env->next;
		ft_free_env(first);
		return ;
	}
	second = g_data->env->next;
	while (second != NULL)
	{
		if (!ft_strcmp(second->name, env_del))
		{
			first->next = second->next;
			ft_free_env(second);
			return ;
		}
		first = first->next;
		second = second->next;
	}
}

int	ft_env_error(char *env_line)
{
	int	i;

	i = 0;
	if (ft_isdigit(env_line[i]))
		return (1);
	while (env_line[i])
	{
		if (!ft_isalnum(env_line[i]) && env_line[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
