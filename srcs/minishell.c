#include "minishell.h"

// void	ft_print_commands(t_cmd *cmd)
// {
// 	t_cmd	*current;
// 	int		i;
// 	char	**temp;

// 	current = cmd;
// 	i = 0;
// 	while (current != NULL)
// 	{
// 		printf("Command group %d:\n", i);
// 		temp = current->cmd;
// 		while (*temp)
// 		{
// 			printf("(%s)\n", *temp);
// 			temp++;
// 		}
// 		current = current->next;
// 		i++;
// 	}
// }

void	ft_l(void)
{
	system("leaks -q minishell");
}

void	ft_minish(char **envp)
{
	t_general	g_data;
	char		*line;

	g_running = 1;
	g_data.cmd = NULL;
	atexit(ft_l);
	ft_dup_env(&g_data, envp);
	g_data.og_in = dup(STDIN_FILENO);
	g_data.og_out = dup(STDOUT_FILENO);
	g_data.status = 0;
	g_data.cpy_line = NULL;
	ft_prompt();
	while (g_running)
	{
		line = readline("\033[0;32mMinishell$ \033[0m");
		if (!line)
			continue ;
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (line && *line)
			add_history(line);
		if (ft_solo_espacios(line) == 1)
		{
			ft_parser(&g_data, line);
			ft_cmd_lst(&g_data, g_data.split_tokens);
			if (ft_cmd_len(&g_data) == 1)
			{
				ft_redir(&g_data, g_data.cmd);
				if (g_data.cmd->cmd[0] != NULL)
				{
					if (!ft_builtins(&g_data, g_data.cmd->cmd))
						g_data.status = ft_other_cmd(&g_data, g_data.cmd->cmd);
				}
			}
			else if (ft_cmd_len(&g_data) >= 2)
			{
				ft_multiple_cmd(&g_data, g_data.cmd);
			}
			// printf("status: %d\n", g_data.status);
			free(g_data.cpy_line);
			ft_free(g_data.split_tokens, ft_mtxrow(g_data.split_tokens));
		}
		dup2(g_data.og_in, STDIN_FILENO);
		dup2(g_data.og_out, STDOUT_FILENO);
		free(line);
		ft_free_cmd(&g_data);
	}
	printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
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