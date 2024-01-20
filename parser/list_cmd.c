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
    ft_process_args(cmd, mtx);
    ft_fill_cmd(cmd, mtx);
    return cmd;
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
