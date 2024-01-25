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



/*
typedef struct s_process_character
{
	char		*token;
	int			*j;
	int			*k;
	int			*in_quotes;
	char		*quote_char;
	char		*temp;
}				t_process_character;


void	process_character(t_process_character *p)
{
	if(p->token[*(p->j)] == '\"' || p->token[*(p->j)] == '\'')
	{
		if (*(p->in_quotes))
		{
			if (p->token[*(p->j)] == *(p->quote_char))
			{
				// Closing quote matches opening quote
				*(p->in_quotes) = 0;
				*(p->quote_char) = '\0';
			}
			else
			{
				// Quote doesn't match opening quote, so copy it
				p->temp[*(p->k)] = p->token[*(p->j)];
				(*(p->k))++;
			}
		}
		else
		{
			// Not in quotes, so start a new quote sequence
			*(p->in_quotes) = 1;
			*(p->quote_char) = p->token[*(p->j)];
		}
		(*(p->j))++;
	}
	else
	{
		p->temp[*(p->k)] = p->token[*(p->j)];
		(*(p->k))++;
		(*(p->j))++;
	}
}

char	*process_token(t_process_character *p)
{
	int	len;

	*(p->j) = 0;
	*(p->k) = 0;
	len = ft_strlen(p->token);
	p->temp = ft_calloc(len + 1, sizeof(char));
	while(p->token[*(p->j)])
	{
		process_character(p);
	}
	p->temp[*(p->k)] = '\0';
	return (p->temp);
}

void	replace_token_in_cmd(t_general *g_data, int i, char *temp)
{
	char	*temp2;

	temp2 = ft_strdup(temp);
	free(g_data->cmd->cmd[i]);
	g_data->cmd->cmd[i] = ft_strdup(temp2);
	free(temp);
	free(temp2);
}

void	ft_quita_comillas(t_general *g_data)
{
	int i = 0;
	int in_quotes = 0;
	char quote_char = '\0';
	char *temp;
	t_process_character p;

	while(g_data->cmd->cmd[i])
	{
		p.token = g_data->cmd->cmd[i];
		p.j = &i;
		p.k = &i;
		p.in_quotes = &in_quotes;
		p.quote_char = &quote_char;
		temp = process_token(&p);
		replace_token_in_cmd(g_data, i, temp);
		i++;
	}
}*/