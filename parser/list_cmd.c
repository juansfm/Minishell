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
/*
t_cmd *ft_init_cmd(void)
{
    t_cmd *cmd = ft_calloc(1, sizeof(t_cmd));
    cmd->infile = -1;
    cmd->outfile = -1;
    return cmd;
}

t_cmd *ft_cmd_new(char *arg)
{
    t_cmd *cmd = ft_init_cmd();
    char **mtx = ft_split(arg, ' ');
	printf("\narg: %s\n", arg);
    ft_process_args(cmd, mtx);
	printf("\nARG: %s\n", arg);
    ft_fill_cmd(cmd, mtx);
	printf("\nARG2222: %s\n", arg);
    return cmd;
}
*/
t_cmd	*ft_cmd_new(char *arg)
{
	t_cmd	*cmd;
	char	**mtx;
	int		i;
	int		j;
	int		len;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->infile = -1;
	cmd->outfile = -1;
	mtx = ft_split(arg, ' ');
	i = -1;
	len = 0;
	while (mtx[++i] != NULL)
	{
		if (!ft_strcmp(mtx[i], "<") && mtx[i + 1] != NULL)
		{
			i++;
			cmd->infile_name = ft_strdup(mtx[i]);
			if (cmd->infile != -1)
				close(cmd->infile);
			cmd->infile = open(cmd->infile_name, O_RDONLY);
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
		
		else
			len++;
	}
	cmd->cmd = ft_calloc(len + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (mtx[++i] != NULL)
	{
		if ((!ft_strcmp(mtx[i], "<") || !ft_strcmp(mtx[i], ">")
				|| !ft_strcmp(mtx[i], ">>")) && mtx[i + 1] != NULL)
			i++;
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
