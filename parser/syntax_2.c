#include "minishell.h"

int	ft_check_quotes(t_general *g_data, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		ft_if_is_quote(line[i], g_data);
	}
	if (g_data->quote_double == 1 || g_data->quote_simple == 1)
	{
		ft_putendl_fd(QUOTE, 1);
		g_data->status = 258;
		return (1);
	}
	if (line[0] == '|')
	{
		ft_putendl_fd(PIPE_ERROR, 1);
		g_data->status = 258;
		return (1);
	}
	return (0);
}

int	ft_syntax_boucle(t_general *g_data, char *line, int *redir, int i)
{
	if (ft_redir_in_error(g_data, line, redir, i))
		return (1);
	if (ft_redir_out_error(g_data, line, redir, i))
		return (1);
	if (line[i] == '|')
	{
		if (redir[0] != 0)
		{
			ft_putendl_fd(PIPE_ERROR, 1);
			g_data->status = 258;
			return (1);
		}
		redir[0] = 5;
	}
	if (ft_redir_out_valor(g_data, line, redir, i))
		return (1);
	if (ft_redir_in_valor(g_data, line, redir, i))
		return (1);
	if (line[i] != '<' && line[i] != '>' && line[i] != '|')
		redir[0] = 0;
	return (0);
}
int	ft_final_redir(t_general *g_data, int redir)
{
	if (redir != 0)
	{
		ft_putendl_fd(NEWLINE_ERROR, 1);
		g_data->status = 258;
		return (1);
	}
	return (0);
}