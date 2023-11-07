/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:57:57 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/11/03 19:00:23 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_env_search(t_general *g_data, char *name)
{
	t_env	*env;

	env = g_data->env;
	while (env != NULL && ft_strcmp(name, env->name))
		env = env->next;
	return (env);
}
