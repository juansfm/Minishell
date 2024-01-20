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
	//char		**mtx;
	g_running = 1;
	//g_data.token = NULL;
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
			printf("\nSe ha ejecutado solo un enter\n");
			continue; // Salir si se presiona Ctrl+D o solo se da enter
		}
		if(line && *line)
			add_history(line);
		ft_parser(&g_data, line);
		//ft_print_tokens(g_data.token);
		ft_cmd_lst(&g_data, g_data.split_tokens);
		//ft_print_commands(g_data.cmd);
		ft_vamos_a_expandir(&g_data);
		ft_restore_quotes(g_data.cmd->cmd);
		
		ft_print_commands(g_data.cmd);
		free(line);
		ft_free_cmd(&g_data);
	}

	// rl_clear_history();
	//temp = g_data.env;
	
	// while (temp != NULL)
	// {
	// 	printf("%s=%s\n", temp->name, temp->valor);
	// 	temp = temp->next;
	// }
	printf("\n");
	//temp = g_data.env;

}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	//signal(SIGINT, ft_sigintHandler);
	if (argc == 1)
	{
		using_history();

		ft_minish(envp);

	}
	else
		printf("Error: too many arguments\n");
	return (0);
}
