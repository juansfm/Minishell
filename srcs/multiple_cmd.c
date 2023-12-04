/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:28:07 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/12/03 18:56:22 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_multiple_cmd(t_general *g_data, t_cmd *cmd)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid == 1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (!ft_builtins(g_data, cmd->cmd))
			ft_other_cmd(g_data, cmd->cmd);
		exit(0);
	}
	else if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (cmd->next)
			ft_multiple_cmd(g_data, cmd->next);
		else
		{
			if (!ft_builtins(g_data, cmd->cmd))
				ft_other_cmd(g_data, cmd->cmd);
		}
		exit(0);
	}
}
