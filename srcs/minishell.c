#include "minishell.h"

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
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	cmd->next = NULL;
	return (cmd);
}

void ft_print_commands(t_cmd *cmd)
{
    t_cmd *current = cmd;
    int i = 0;

    while (current != NULL) {
        printf("Command %d:\n", i);
        char **temp = current->cmd;
        while (*temp) {
            printf("(%s)\n", *temp);
            temp++;
        }
        current = current->next;
        i++;
    }
}
/* nuevo creo que desecho
void ft_cmd_lst(t_general *g_data)
{
    t_cmd *cmd;
    t_token *current_token = g_data->token;
    int i = 0;

    while (current_token && current_token->type_token != TOKEN_PIPE)
    {
        cmd = ft_cmd_new(current_token->value);
        ft_cmd_add_back(g_data, cmd);
        current_token = current_token->next;
        i++;
    }

    // Si encontramos un pipe, avanzamos al siguiente token
    if (current_token && current_token->type_token == TOKEN_PIPE)
    {
        g_data->token = current_token->next;
    }
}
*/
//antiguo(de juan)
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

void	ft_l(void)
{
	system("leaks -q Minishell");
}


void	ft_minish(char **envp)
{
	t_general	g_data;
	char		*line;
	//char		**mtx;
	g_running = 1;
	g_data.token = NULL;
	g_data.cmd = NULL;
	//atexit(ft_l);
	ft_dup_env(&g_data, envp);
	while (g_running)
	{
		line = readline("Minishell$ ");
		if (!line)
		{
			printf("\nSaliendo minishell(Ctrl+D)");
			break ; // Salir si se presiona Ctrl+D o solo se da enter
		}
		//comprobar frase
		//|ft_syntaxis(&g_data, line);
		//line = ft_strtrim(line, " ");
		//mtx = ft_split(line, '|');
		if(line && *line)
			add_history(line);
			
		ft_parser(&g_data, line);
		//ft_print_tokens(g_data.token);

		ft_cmd_lst(&g_data, g_data.split_tokens);
		ft_restore_quotes(g_data.cmd->cmd);
		if (!ft_builtins(&g_data, g_data.cmd->cmd))
			ft_other_cmd(&g_data, g_data.cmd->cmd);
            //break; // Salir si se presiona Ctrl+D o solo se da enter*/
		//g_data.token = ft_convert_to_tokens(g_data.split_tokens);
		//ft_cmd_lst(&g_data);
		

		//ft_print_commands(g_data.cmd);
		//int i = 0;
		/*while(g_data.split_tokens[i])
		{
			printf("\033[0;33m");
			printf("\ng_data-split_tokenes: %s\n", g_data.split_tokens[i]);
			printf("\033[0m");
			i++;
		}*/

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


/*
//ls "aaa aa"|grep "a a">"asd"
void ft_syntaxis_error(t_general g_data, char *line)
{

}
*/

//otra cosa es que debo separar los comandos por pipes
//luego tengo que tener en cuenta las redirecciones
//porque si las hubieses tendria que modificar el orden de los valores del comando
//HAcer funcion que me separe los comandos por pipes y me junte los comandos como si fueran frase
//es decir split por pipes y juntar distintos nodos de la lista tokens para convertirlos en t_cmd