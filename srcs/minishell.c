/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:44:57 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/12/03 18:55:40 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_l(void)
{
	system("leaks -q Minishell");
}

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
t_cmd	*ft_cmd_new(char *arg)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->cmd = ft_split(arg, ' ');
	cmd->infile = 0;
	cmd->outfile = 1;
	cmd->next = NULL;
	return (cmd);
}
void	ft_cmd_lst(t_general *g_data, char **mtx)
{
	t_cmd	*cmd;
	t_cmd	*temp;
	int		i;

	temp = g_data->cmd;
	i = -1;
	while (mtx[++i])
	{
		cmd = ft_cmd_new(mtx[i]);
		ft_cmd_add_back(g_data, cmd);
	}
}
void	ft_free_cmd(t_general *g_data)
{
	t_cmd	*temp;

	while (g_data->cmd != NULL)
	{
		temp = g_data->cmd;
		g_data->cmd = g_data->cmd->next;
		ft_free(temp->cmd, ft_mtxrow(temp->cmd));
		free(temp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_general	g_data;
	char		*line;
	char		**mtx;

	// atexit(ft_l);
	//silencia mensajes como ^C cuando ejecuta una señal
	// rl_catch_signals = 0;
	(void)argc;
	(void)argv;
	ft_dup_env(&g_data, envp);
	while (1)
	{
		line = readline("Minishell$");
		// printf("%s\n", line);
		if (line)
		{
			line = ft_strtrim(line, " ");
			mtx = ft_split(line, '|');
			ft_cmd_lst(&g_data, mtx);
			if (ft_cmd_len(&g_data) == 1)
			{
				if (!ft_builtins(&g_data, g_data.cmd->cmd))
					ft_other_cmd(&g_data, g_data.cmd->cmd);
			}
			else if (ft_cmd_len(&g_data) >= 2)
				ft_multiple_cmd(&g_data, g_data.cmd);
			// free(line2);
			// ft_free(mtx, ft_mtxrow(mtx));
			ft_free_cmd(&g_data);
		}
	}
}
