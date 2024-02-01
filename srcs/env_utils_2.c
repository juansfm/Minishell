/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agil-ord <agil-ord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:48:58 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/02/01 15:03:30 by agil-ord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Search a env variable by its name (w/o $)
 * 
 * @param g_data general struct
 * @param name name of the env variable
 * @return t_env* 
 */
t_env	*ft_env_search(t_general *g_data, char *name)
{
	t_env	*env;

	env = g_data->env;
	while (env != NULL && ft_strcmp(name, env->name))
		env = env->next;
	return (env);
}

/**
 * @brief Return the length of the struct t_env
 * 
 * @param g_data general struct
 * @return int 
 */
int	ft_env_len(t_general *g_data)
{
	t_env	*temp;
	int		i;

	temp = g_data->env;
	i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
