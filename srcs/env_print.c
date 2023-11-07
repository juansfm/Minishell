/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:58:04 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/11/01 13:45:00 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (temp->valor)
				ft_putstr_fd(temp->valor, 1);
			ft_putchar_fd('\n', 1);
		}
		temp = temp->next;
	}
}

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
			if (temp->valor)
				ft_putstr_fd(temp->valor, 1);
		}
		ft_putchar_fd('\n', 1);
		temp = temp->next;
	}
	// t_env	*first;
	// t_env	*second;
	// t_env	*new;
	// t_env	*inx;

	// new = g_data->env;
	// inx = g_data->env->next;
	// if ()
	// while (inx != NULL)
	// // first = g_data->env;
	// // second = g_data->env->next;
}
