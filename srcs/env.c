/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:49:04 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/01/28 16:49:05 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Duplicate env variables of the shell
 * 
 * @param g_data general struct
 * @param envp original env variables
 */
void	ft_dup_env(t_general *g_data, char **envp)
{
	t_env	*node;
	int		i;

	g_data->env = NULL;
	i = -1;
	while (envp[++i])
	{
		node = ft_env_new(envp[i]);
		ft_env_add_back(g_data, node);
	}
}

/**
 * @brief Add a env variable or modify if it exists
 * 
 * @param g_data general struct
 * @param env_new NAME=VALUE form
 */
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
			free(temp->value);
			temp->equal = 1;
			temp->value = ft_strdup(new->value);
			ft_free_env(new);
			return ;
		}
		temp = temp->next;
	}
	ft_env_add_back(g_data, new);
}

/**
 * @brief Delete a env variable
 * 
 * @param g_data general struct
 * @param env_del name of the env variable to delete (w/o $)
 */
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

/**
 * @brief Find out if env variable has a valid name
 * 
 * @param env_line name of the env variable
 * @return int 1 if exists an error and 0 if it's correct
 */
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
