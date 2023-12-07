#include "minishell.h"
int g_running = 1;
/*
void	ft_l(void)
{
	system("leaks -q Minishell");
}
*/

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


void	ft_l(void)
{
	system("leaks -q Minishell");
}
/*
void ft_sigintHandler(int signal)
{
    printf("\nCtrl+C detectado. Saliendo de Minishell...\n");
    g_running = 0;
}
*/

void ft_minish(char **envp)
{
	t_general	g_data;
	char		*line;
	t_env		*temp;
	//char		**mtx;
	(void)envp;
	
	g_data.token = NULL;
	//atexit(ft_l);
	ft_dup_env(&g_data, envp);
	while (g_running)
	{
		line = readline("Minishell$ ");
		if (!line) 
		{
			printf("\nSaliendo minishell(Ctrl+D)");
            break; // Salir si se presiona Ctrl+D o solo se da enter
    	}
		printf("%s\n", line);
		if(!line)
			break;
		if (line)
		{
			free(line); // Liberar la memoria asignada por readline
			printf("\nsaliendo minishell (exit)");
			break ;

		}
		ft_parser(&g_data, line);
		free(line);
	}
	// rl_clear_history();
	temp = g_data.env;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->name, temp->valor);
		temp = temp->next;
	}
	printf("\n");
	temp = g_data.env;

}

int main(int argc, char **argv, char **envp)
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