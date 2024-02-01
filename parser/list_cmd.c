/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:48:01 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/01/28 16:48:02 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmd_last(t_general *g_data)
{
	t_cmd	*temp;

	temp = g_data->cmd;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	ft_cmd_add_back(t_general *g_data, t_cmd *new)
{
	t_cmd	*temp;

	if (g_data->cmd == NULL)
		g_data->cmd = new;
	else
	{
		temp = ft_cmd_last(g_data);
		temp->next = new;
	}
}

void	ft_cmd_lst(t_general *g_data, char **mtx)
{
	t_cmd	*cmd;
	int		i;

	i = -1;
	while (mtx[++i])
	{
		cmd = ft_cmd_new(mtx[i]);
		ft_cmd_add_back(g_data, cmd);
	}
}
