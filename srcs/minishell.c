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
	// atexit(ft_l);
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
			exit(EXIT_FAILURE);
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
				if (g_running == 1 && g_data.cmd->cmd[0] != NULL)
				{
					g_running = 3;
					if (!ft_builtins(&g_data, g_data.cmd->cmd))
						g_data.status = ft_other_cmd(&g_data,
								g_data.cmd->cmd);
				}
			}
			else if (ft_cmd_len(&g_data) >= 2)
			{
				ft_multiple_cmd(&g_data, g_data.cmd);
			}
			free(g_data.cpy_line);
			ft_free(g_data.split_tokens, ft_mtxrow(g_data.split_tokens));
		}
		dup2(g_data.og_in, STDIN_FILENO);
		dup2(g_data.og_out, STDOUT_FILENO);
		free(line);
		ft_free_cmd(&g_data);
		g_running = 1;
	}
	printf("\n");
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
// void	ft_handler(int sig)
// {
// 	if (SIGINT == sig && g_running == 3)
// 	{
// 		g_running = 0;
// 		rl_replace_line("", 0);
// 		ft_putstr_fd("   \n", 1);
// 	}
// 	else if (SIGINT == sig && g_running == 2)
// 	{
// 		g_running = 0;
// 		ioctl(STDIN_FILENO, TIOCSTI, "\n");
// 	}
// 	else if (SIGINT == sig)
// 	{
// 		g_running = 1;
// 		rl_on_new_line();
// 		rl_redisplay();
// 		rl_replace_line("", 0);
// 		ft_putstr_fd("   \n", 1);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

// void	ft_ctrl_d(t_general *g_data)
// {
// 	if (!g_data->cmd)
// 	{
// 		rl_on_new_line();
// 		rl_redisplay();
// 		ft_putstr_fd("exit\n", 1);
// 		rl_clear_history();
// 		ft_free_cmd(g_data);
// 		exit(EXIT_SUCCESS);
// 	}
// }
