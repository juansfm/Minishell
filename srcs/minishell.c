/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:49:10 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/01/28 16:49:11 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_l(void)
// {
// 	system("leaks -q minishell");
// }

void	ft_init_data(t_general *g_data)
{
	g_running = 1;
	g_data->cmd = NULL;
	g_data->og_in = dup(STDIN_FILENO);
	g_data->og_out = dup(STDOUT_FILENO);
	g_data->status = 0;
	g_data->cpy_line = NULL;
	g_data->quote_simple = 0;
	g_data->quote_double = 0;
	ft_delete_env(g_data, "OLDPWD");
	ft_prompt();
}

void	ft_principal_boucle(t_general *g_data, char *line)
{
	ft_parser(g_data, line);
	ft_cmd_lst(g_data, g_data->split_tokens);
	if (ft_cmd_len(g_data) == 1)
	{
		ft_redir(g_data, g_data->cmd);
		if (g_running == 1 && g_data->cmd->cmd[0] != NULL)
		{
			g_running = 3;
			if (!ft_builtins(g_data, g_data->cmd->cmd))
				g_data->status = ft_other_cmd(g_data, g_data->cmd->cmd);
			if (g_running == -3)
				g_data->status = 130;
		}
	}
	else if (ft_cmd_len(g_data) >= 2)
		ft_multiple_cmd(g_data, g_data->cmd);
	free(g_data->cpy_line);
	ft_free(g_data->split_tokens, ft_mtxrow(g_data->split_tokens));
}

void	ft_restore(t_general *g_data, char *line)
{
	dup2(g_data->og_in, STDIN_FILENO);
	dup2(g_data->og_out, STDOUT_FILENO);
	free(line);
	ft_free_cmd(g_data);
	g_running = 1;
}

//atexit(ft_l);
void	ft_minish(char **envp)
{
	t_general	g_data;
	char		*line;

	ft_dup_env(&g_data, envp);
	ft_init_data(&g_data);
	while (g_running)
	{
		g_data.quote_simple = 0;
		g_data.quote_double = 0;
		line = readline("\033[0;32mMinishell$ \033[0m");
		if (!line)
			exit(EXIT_FAILURE);
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (line && *line)
			add_history(line);
		if ((ft_only_spaces(line)) == 1 && ft_syntax_error(&g_data, line) == 0)
			ft_principal_boucle(&g_data, line);
		ft_restore(&g_data, line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handler);
	(void)argv;
	if (argc == 1)
	{
		using_history();
		ft_minish(envp);
	}
	else
		printf("Error: too many arguments\n");
	return (0);
}
