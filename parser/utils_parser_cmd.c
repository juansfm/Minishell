#include "minishell.h"

void ft_process_args(t_cmd *cmd, char **mtx)
{
    int i = -1;
    int len = 0;
    while (mtx[++i] != NULL)
    {
        if (!ft_strcmp(mtx[i], "<") && mtx[i + 1] != NULL)
            ft_process_input(cmd, mtx, &i);
        else if (!ft_strcmp(mtx[i], ">") && mtx[i + 1] != NULL)
            ft_process_output(cmd, mtx, &i, 0);
        else if (!ft_strcmp(mtx[i], ">>") && mtx[i + 1] != NULL)
            ft_process_output(cmd, mtx, &i, 1);
        else
            len++;
    }
    cmd->cmd = ft_calloc(len + 1, sizeof(char *));
}

void ft_fill_cmd(t_cmd *cmd, char **mtx)
{
    int i = -1;
    int j = 0;
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
    cmd->next = NULL;
}

void ft_process_input(t_cmd *cmd, char **mtx, int *i)
{
    (*i)++;
    cmd->infile_name = ft_strdup(mtx[*i]);
    if (cmd->infile != -1)
        close(cmd->infile);
    cmd->infile = open(cmd->infile_name, O_RDONLY);
}

void ft_process_output(t_cmd *cmd, char **mtx, int *i, int append)
{
    (*i)++;
    cmd->outfile_name = ft_strdup(mtx[*i]);
    if (cmd->outfile != -1)
        close(cmd->outfile);
    if (append)
        cmd->outfile = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        cmd->outfile = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	ft_free_cmd(t_general *g_data)
{
	t_cmd	*temp;

	while (g_data->cmd != NULL)
	{
		temp = g_data->cmd;
		g_data->cmd = g_data->cmd->next;
		ft_free(temp->cmd, ft_mtxrow(temp->cmd));
		free(temp->infile_name);
		free(temp->outfile_name);
		free(temp);
	}
}
