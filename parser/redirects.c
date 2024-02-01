/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agil-ord <agil-ord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:48:09 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/02/01 15:01:31 by agil-ord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_input_file(t_cmd *cmd, char **mtx, t_cmd_data *data)
{
	data->i++;
	cmd->infile_name = ft_strdup(mtx[data->i]);
	if (cmd->infile != -1)
		close(cmd->infile);
	cmd->infile = open(cmd->infile_name, O_RDONLY, 0644);
}

void	ft_process_output_file(t_cmd *cmd, char **mtx, t_cmd_data *data)
{
	data->i++;
	cmd->outfile_name = ft_strdup(mtx[data->i]);
	if (cmd->outfile != -1)
		close(cmd->outfile);
	cmd->outfile = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	ft_process_redirects(t_cmd *cmd, char **mtx, t_cmd_data *data)
{
	if (!ft_strcmp(mtx[data->i], "<") && mtx[data->i + 1] != NULL)
		ft_process_input_file(cmd, mtx, data);
	else if (!ft_strcmp(mtx[data->i], ">") && mtx[data->i + 1] != NULL)
		ft_process_output_file(cmd, mtx, data);
	else if (!ft_strcmp(mtx[data->i], ">>") && mtx[data->i + 1] != NULL)
	{
		data->i++;
		cmd->outfile_name = ft_strdup(mtx[data->i]);
		cmd->outfile = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_APPEND,
				0644);
	}
	else if (!ft_strcmp(mtx[data->i], "<<") && mtx[data->i + 1] != NULL)
	{
		data->i++;
		data->lenh++;
	}
	else
		data->len++;
}

void	ft_fill_cmd_and_heredoc(t_cmd *cmd, char **mtx, t_cmd_data *data)
{
	while (mtx[++data->i] != NULL)
	{
		if ((!ft_strcmp(mtx[data->i], "<") || !ft_strcmp(mtx[data->i], ">")
				|| !ft_strcmp(mtx[data->i], ">>")) && mtx[data->i + 1] != NULL)
			data->i++;
		else if (!ft_strcmp(mtx[data->i], "<<"))
		{
			data->i++;
			cmd->heredoc[data->k] = ft_strdup(mtx[data->i]);
			data->k++;
		}
		else
		{
			cmd->cmd[data->j] = ft_strdup(mtx[data->i]);
			data->j++;
		}
	}
}

t_cmd	*ft_cmd_new(char *arg)
{
	t_cmd		*cmd;
	char		**mtx;
	t_cmd_data	data;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->pos_ult_dolar = -1;
	mtx = ft_split(arg, ' ');
	data.i = -1;
	data.len = 0;
	data.lenh = 0;
	while (mtx[++data.i] != NULL)
		ft_process_redirects(cmd, mtx, &data);
	cmd->cmd = ft_calloc(data.len + 1, sizeof(char *));
	if (data.lenh > 0)
		cmd->heredoc = ft_calloc(data.lenh + 1, sizeof(char *));
	data.i = -1;
	data.j = 0;
	data.k = 0;
	ft_fill_cmd_and_heredoc(cmd, mtx, &data);
	cmd->next = NULL;
	ft_free(mtx, ft_mtxrow(mtx));
	return (cmd);
}
