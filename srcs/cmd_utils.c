/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:48:41 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/01/28 16:48:42 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_len(t_general *g_data)
{
	t_cmd	*temp;
	int		i;

	temp = g_data->cmd;
	i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	**ft_union_cmd_arg(char *cmd, char **arg)
{
	char	**mtx;
	int		i;

	i = ft_mtxrow(arg) + 2;
	mtx = ft_calloc(i, sizeof(char *));
	mtx[0] = ft_strdup(cmd);
	if (!arg)
		return (mtx);
	i = -1;
	while (arg[++i])
		mtx[i + 1] = ft_strdup(arg[i]);
	return (mtx);
}
