#include "minishell.h"

void	ft_print_commands(t_cmd *cmd)
{
	t_cmd	*current;
	int		i;
	char	**temp;

	current = cmd;
	i = 0;
	while (current != NULL)
	{
		printf("Command group %d:\n", i);
		temp = current->cmd;
		while (*temp)
		{
			printf("(%s)\n", *temp);
			temp++;
		}
		current = current->next;
		i++;
	}
}
/*

void	ft_quita_comillas(t_general *g_data)
{
    int i;
    int j;
    int k;
    int len;
    int in_quotes;
    char quote_char;
    char *temp;
    char *temp2;

    i = 0;
    j = 0;
    k = 0;
    len = 0;
    in_quotes = 0;
    quote_char = '\0';
    temp = NULL;
    temp2 = NULL;
    while(g_data->cmd->cmd[i])
    {
        len = ft_strlen(g_data->cmd->cmd[i]);
        temp = ft_calloc(len + 1, sizeof(char));
        temp2 = ft_calloc(len + 1, sizeof(char));
        while(g_data->cmd->cmd[i][j])
        {
            if(g_data->cmd->cmd[i][j] == '\"' || g_data->cmd->cmd[i][j] == '\'')
            {
                if (in_quotes)
                {
                    if (g_data->cmd->cmd[i][j] == quote_char)
                    {
                        // Closing quote matches opening quote
                        in_quotes = 0;
                        quote_char = '\0';
                    }
                    else
                    {
                        // Quote doesn't match opening quote, so copy it
                        temp[k] = g_data->cmd->cmd[i][j];
                        k++;
                    }
                }
                else
                {
                    // Not in quotes, so start a new quote sequence
                    in_quotes = 1;
                    quote_char = g_data->cmd->cmd[i][j];
                }
                j++;
            }
            else
            {
                temp[k] = g_data->cmd->cmd[i][j];
                k++;
                j++;
            }
        }
        temp[k] = '\0';
        temp2 = ft_strdup(temp);
        free(g_data->cmd->cmd[i]);
        g_data->cmd->cmd[i] = ft_strdup(temp2);
        free(temp);
        free(temp2);
        i++;
        j = 0;
        k = 0;
    }
}
*/
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
		if (ft_solo_espacios(line) == 1)
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
		printf("status: %d\n", g_data.status);
	}
	//ft_print_commands(g_data.cmd);
	//ft_print_commands(g_data.cmd);
	//free(line);
	//ft_free_cmd(&g_data);
	// rl_clear_history();
	//temp = g_data.env;
	// while (temp != NULL)
	// {
	// 	printf("%s=%s\n", temp->name, temp->valor);
	// 	temp = temp->next;
	// }
	printf("\n");
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
