#include "minishell.h"

void	ft_process_quote_character(t_process_data *p)
{
	if (p->in_quotes)
	{
		if (p->g_data->cmd->cmd[p->i][p->j] == p->quote_char)
		{
			p->in_quotes = 0;
			p->quote_char = '\0';
		}
		else
		{
			p->temp[p->k] = p->g_data->cmd->cmd[p->i][p->j];
			p->k++;
		}
	}
	else
	{
		p->in_quotes = 1;
		p->quote_char = p->g_data->cmd->cmd[p->i][p->j];
	}
	p->j++;
}

void	ft_process_non_quote_character(t_process_data *p)
{
	p->temp[p->k] = p->g_data->cmd->cmd[p->i][p->j];
	p->k++;
	p->j++;
}

void	ft_process_character(t_process_data *p)
{
	if (p->g_data->cmd->cmd[p->i][p->j] == '\"'
		|| p->g_data->cmd->cmd[p->i][p->j] == '\'')
	{
		ft_process_quote_character(p);
	}
	else
	{
		ft_process_non_quote_character(p);
	}
}

void	ft_process_token(t_process_data *p)
{
	int	len;

	len = ft_strlen(p->g_data->cmd->cmd[p->i]);
	p->temp = ft_calloc(len + 1, sizeof(char));
	while (p->g_data->cmd->cmd[p->i][p->j])
		ft_process_character(p);
	p->temp[p->k] = '\0';
}

void	ft_replace_token_in_cmd(t_process_data *p)
{
	char	*temp2;

	temp2 = ft_strdup(p->temp);
	free(p->g_data->cmd->cmd[p->i]);
	p->g_data->cmd->cmd[p->i] = ft_strdup(temp2);
	free(p->temp);
	free(temp2);
}
