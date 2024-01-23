#include "minishell.h"
int		g_running = 1;

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
	char	**mtx;
	int		i;
	int		j;
	int		k;
	int		len;
	int		lenh;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->infile = -1;
	cmd->outfile = -1;
	mtx = ft_split(arg, ' ');
	i = -1;
	len = 0;
	lenh = 0;
	while (mtx[++i] != NULL)
	{
		if (!ft_strcmp(mtx[i], "<") && mtx[i + 1] != NULL)
		{
			i++;
			cmd->infile_name = ft_strdup(mtx[i]);
			if (cmd->infile != -1)
				close(cmd->infile);
			cmd->infile = open(cmd->infile_name, O_RDONLY, 0777);
		}
		else if (!ft_strcmp(mtx[i], ">") && mtx[i + 1] != NULL)
		{
			i++;
			cmd->outfile_name = ft_strdup(mtx[i]);
			if (cmd->outfile != -1)
				close(cmd->outfile);
			cmd->outfile = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (!ft_strcmp(mtx[i], ">>") && mtx[i + 1] != NULL)
		{
			i++;
			cmd->outfile_name = ft_strdup(mtx[i]);
			cmd->outfile = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else if (!ft_strcmp(mtx[i], "<<") && mtx[i + 1] != NULL)
		{
			i++;
			// cmd->heredoc = ft_strdup(mtx[i]);
			lenh++;
		}
		else
			len++;
	}
	cmd->cmd = ft_calloc(len + 1, sizeof(char *));
	if (lenh > 0)
		cmd->heredoc = ft_calloc(lenh + 1, sizeof(char *));
	i = -1;
	j = 0;
	k = 0;
	while (mtx[++i] != NULL)
	{
		if ((!ft_strcmp(mtx[i], "<") || !ft_strcmp(mtx[i], ">") || !ft_strcmp(mtx[i], ">>")) && mtx[i + 1] != NULL)
			i++;
		else if (!ft_strcmp(mtx[i], "<<"))
		{
			i++;
			cmd->heredoc[k] = ft_strdup(mtx[i]);
			k++;
		}
		else
		{
			cmd->cmd[j] = ft_strdup(mtx[i]);
			j++;
		}
	}
	// cmd->cmd = ft_split(arg, ' ');
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
		ft_free(temp->heredoc, ft_mtxrow(temp->heredoc));
		free(temp->infile_name);
		free(temp->outfile_name);
		free(temp);
	}
}

void	ft_l(void)
{
	system("leaks -q minishell");
}
/*
void	ft_sigintHandler(int signal)
{
	printf("\nCtrl+C detectado. Saliendo de Minishell...\n");
	g_running = 0;
}
*/

void	ft_minish(char **envp)
{
	t_general	g_data;
	char		*line;
	char		**mtx;

	g_data.token = NULL;
	g_data.cmd = NULL;
	atexit(ft_l);
	ft_dup_env(&g_data, envp);
	g_data.og_in = dup(STDIN_FILENO);
	g_data.og_out = dup(STDOUT_FILENO);
	while (1)
	{
		line = readline("Minishell$ ");
		// printf("HOLA\n");
		// if (!line)
		// 	break ;
		// if (!ft_strcmp(line, "\0"))
		// 	continue ; // Salir si se presiona Ctrl+D o solo se da enter
		add_history(line);
		line = ft_strtrim(line, " ");
		mtx = ft_split(line, '|');
		ft_cmd_lst(&g_data, mtx);
		if (ft_cmd_len(&g_data) == 1)
		{
			ft_redir(&g_data, g_data.cmd);
			if (!ft_builtins(&g_data, g_data.cmd->cmd))
				ft_other_cmd(&g_data, g_data.cmd->cmd);
		}
		else if (ft_cmd_len(&g_data) >= 2)
			ft_multiple_cmd(&g_data, g_data.cmd);
		// ft_parser(&g_data, line);
		dup2(g_data.og_in, STDIN_FILENO);
		dup2(g_data.og_out, STDOUT_FILENO);
		if (g_data.cmd != NULL)
			ft_free_cmd(&g_data);
	}
	// rl_clear_history();
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
