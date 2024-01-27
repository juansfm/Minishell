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
void	ft_entrecomillas(char char_cmd, t_general *g_data)
{
	int	i;

	i = 0;
	if (char_cmd == '\"' && g_data->quote_double == 0
		&& g_data->quote_simple == 0)
		g_data->quote_double = 1;
	else if (char_cmd == '\'' && g_data->quote_double == 0
			&& g_data->quote_simple == 0)
		g_data->quote_simple = 1;
	else if (char_cmd == '\"' && g_data->quote_double == 1)
		g_data->quote_double = 0;
	else if (char_cmd == '\'' && g_data->quote_simple == 1)
		g_data->quote_simple = 0;
}

int	ft_syntax_error(t_general *g_data, char *line)
{
	int	i;
	int	redir;

	redir = 0;
	i = -1;
	while (line[++i])
	{
		ft_entrecomillas(line[i], g_data);
	}
	if (g_data->quote_double == 1 || g_data->quote_simple == 1)
	{
		ft_putendl_fd(QUOTE, 1);
		return (1);
	}
	i = -1;
	if (line[0] == '|')
	{
		ft_putendl_fd(PIPE_ERROR, 1);
		return (1);
	}
	while (line[++i])
	{
		if (line[i] == ' ')
			continue ;
		ft_entrecomillas(line[i], g_data);
		if (g_data->quote_double == 1 || g_data->quote_simple == 1)
			continue ;
		if (i == 0)
		{
			if (line[i] == '>')
				redir = 1;
			else if (line[i] == '<')
				redir = 3;
			if (line[i] == '>' || line[i] == '<')
				continue ;
		}
		if (line[i] == '<' && line[i - 1] != '<')
		{
			if ((redir > 0 && redir < 5) && line[i + 1] != '<')
			{
				ft_putendl_fd(REDIR_ERROR_1, 1);
				return (1);
			}
			if ((redir > 0 && redir < 5) && line[i + 1] == '<')
			{
				ft_putendl_fd(REDIR_ERROR_2, 1);
				return (1);
			}
		}
		if (line[i] == '>' && line[i - 1] != '>')
		{
			if ((redir > 0 && redir < 5) && line[i + 1] != '>')
			{
				ft_putendl_fd(REDIR_ERROR_3, 1);
				return (1);
			}
			if ((redir > 0 && redir < 5) && line[i + 1] == '>')
			{
				ft_putendl_fd(REDIR_ERROR_4, 1);
				return (1);
			}
		}
		if (line[i] == '|')
		{
			if (redir != 0)
			{
				ft_putendl_fd(PIPE_ERROR, 1);
				return (1);
			}
			redir = 5;
		}
		if (line[i] == '<')
		{
			if (line[i - 1] == '<' && line[i - 2] == '<')
			{
				ft_putendl_fd(REDIR_ERROR_1, 1);
				return (1);
			}
			if (line[i - 1] != '<')
				redir = 1;
			else
				redir = 2;
		}
		if (line[i] == '>')
		{
			if (line[i - 1] == '>' && line[i - 2] == '>')
			{
				ft_putendl_fd(REDIR_ERROR_3, 1);
				return (1);
			}
			if (line[i - 1] != '>')
				redir = 3;
			else
				redir = 4;
		}
		if (line[i] != '<' && line[i] != '>' && line[i] != '|')
			redir = 0;
	}
	if (redir != 0)
	{
		ft_putendl_fd(NEWLINE_ERROR, 1);
		return (1);
	}
	return (0);
}

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
	//atexit(ft_l);
	ft_dup_env(&g_data, envp);
	g_data.og_in = dup(STDIN_FILENO);
	g_data.og_out = dup(STDOUT_FILENO);
	g_data.status = 0;
	g_data.cpy_line = NULL;
	g_data.quote_simple = 0;
	g_data.quote_double = 0;
	ft_prompt();
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
		if ((ft_solo_espacios(line)) == 1 && ft_syntax_error(&g_data, line) == 0)
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
