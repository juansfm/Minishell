/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:49:01 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/01/28 16:49:02 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_add_back(t_general *g_data, t_env *new)
{
	t_env	*temp;

	if (g_data->env == NULL)
		g_data->env = new;
	else
	{
		temp = ft_env_last(g_data);
		temp->next = new;
	}
}

t_env	*ft_env_last(t_general *g_data)
{
	t_env	*temp;

	temp = g_data->env;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}

t_env	*ft_env_new(char *env_line)
{
	t_env	*env;
	char	**matrix;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	if (!ft_strchr(env_line, '='))
	{
		env->name = ft_strdup(env_line);
		env->value = ft_strdup("\0");
		env->equal = 0;
	}
	else
	{
		matrix = ft_env_split(env_line, '=');
		env->name = ft_strdup(matrix[0]);
		env->value = ft_strdup(matrix[1]);
		env->equal = 1;
		ft_free(matrix, ft_mtxrow(matrix));
	}
	env->next = NULL;
	return (env);
}

void	ft_free_env(t_env *env)
{
	free(env->name);
	free(env->value);
	env->next = NULL;
	free(env);
}

char	**ft_env_split(char *line, char c)
{
	int		i;
	char	**matrix;

	i = -1;
	if (line[0] == '=')
		i++;
	while (line[++i])
	{
		if (line[i] == c)
			break ;
	}
	matrix = ft_calloc(3, sizeof(char *));
	matrix[0] = ft_substr(line, 0, i);
	matrix[1] = ft_substr(line, i + 1, ft_strlen(line));
	return (matrix);
}
