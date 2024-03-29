/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agil-ord <agil-ord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:48:54 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/02/01 15:03:28 by agil-ord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief print env variables when env
 * 
 * @param g_data general struct
 */
void	ft_print_env(t_general *g_data)
{
	t_env	*temp;

	temp = g_data->env;
	while (temp != NULL)
	{
		if (temp->equal)
		{
			ft_putstr_fd(temp->name, 1);
			ft_putchar_fd('=', 1);
			if (temp->value)
				ft_putstr_fd(temp->value, 1);
			ft_putchar_fd('\n', 1);
		}
		temp = temp->next;
	}
}

/**
 * @brief print env variables when export
 * 
 * @param g_data general struct
 */
void	ft_print_export(t_general *g_data)
{
	t_env	*temp;

	temp = g_data->env;
	while (temp != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(temp->name, 1);
		if (temp->equal)
		{
			ft_putchar_fd('=', 1);
			if (temp->value)
				ft_putstr_fd(temp->value, 1);
		}
		ft_putchar_fd('\n', 1);
		temp = temp->next;
	}
}
