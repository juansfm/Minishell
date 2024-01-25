#include "minishell.h"

void ft_print_commands(t_cmd *cmd)
{
    t_cmd *current = cmd;
    int i = 0;

    while (current != NULL)
	{
        printf("Command group %d:\n", i);
        char **temp = current->cmd;
        while (*temp)
		{
            printf("(%s)\n", *temp);
            temp++;
        }
        current = current->next;
        i++;
    }
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
	ft_prompt();
	while (g_running)
	{
		line = readline("\033[0;32mMinishell$ \033[0m");
		if (!line || line[0] == '\0')
		{
			continue ;
		}
		if (line && *line)
			add_history(line);
		//ft_fucncion_syntax_error(line);
		if(ft_solo_espacios(line) == 1)
		{
			ft_parser(&g_data, line);
			ft_cmd_lst(&g_data, g_data.split_tokens);
			if (ft_cmd_len(&g_data) == 1)
			{
				ft_redir(&g_data, g_data.cmd);
				if (!ft_builtins(&g_data, g_data.cmd->cmd))
					ft_other_cmd(&g_data, g_data.cmd->cmd);
			}
			else if (ft_cmd_len(&g_data) >= 2)
			{
				ft_multiple_cmd(&g_data, g_data.cmd);
			}
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
