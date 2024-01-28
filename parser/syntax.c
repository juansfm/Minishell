#include "minishell.h"

int	ft_syntax_error(t_general *g_data, char *line)
{
	int	i;
	int	redir;

	redir = 0;
	if (ft_check_quotes(g_data, line))
		return (1);
	i = 0;
	if (line[0] == '>')
		redir = 1;
	if (line[0] == '<')
		redir = 2;
	ft_if_is_quote(line[0], g_data);
	while (line[++i])
	{
		if (line[i] == ' ')
			continue ;
		ft_if_is_quote(line[i], g_data);
		if (g_data->quote_double == 1 || g_data->quote_simple == 1)
			continue ;
		if (ft_syntax_boucle(g_data, line, &redir, i))
			return (1);
	}
	ft_final_redir(g_data, redir);
	return (0);
}

int	ft_redir_out_error(t_general *g_data, char *line, int *redir, int i)
{
	if (line[i] == '<' && line[i - 1] != '<')
	{
		if ((redir[0] > 0 && redir[0] < 5) && line[i + 1] != '<')
		{
			ft_putendl_fd(REDIR_ERROR_1, 1);
			g_data->status = 258;
			return (1);
		}
		if ((redir[0] > 0 && redir[0] < 5) && line[i + 1] == '<')
		{
			ft_putendl_fd(REDIR_ERROR_2, 1);
			g_data->status = 258;
			return (1);
		}
	}
	return (0);
}

int	ft_redir_in_error(t_general *g_data, char *line, int *redir, int i)
{
	if (line[i] == '>' && line[i - 1] != '>')
	{
		if ((redir[0] > 0 && redir[0] < 5) && line[i + 1] != '>')
		{
			ft_putendl_fd(REDIR_ERROR_3, 1);
			g_data->status = 258;
			return (1);
		}
		if ((redir[0] > 0 && redir[0] < 5) && line[i + 1] == '>')
		{
			ft_putendl_fd(REDIR_ERROR_4, 1);
			g_data->status = 258;
			return (1);
		}
	}
	return (0);
}

int	ft_redir_out_valor(t_general *g_data, char *line, int *redir, int i)
{
	if (line[i] == '<')
	{
		if (i > 1 && line[i - 1] == '<' && line[i - 2] == '<')
		{
			ft_putendl_fd(REDIR_ERROR_1, 1);
			g_data->status = 258;
			return (1);
		}
		if (line[i - 1] != '<')
			redir[0] = 1;
		else
			redir[0] = 2;
	}
	return (0);
}

int	ft_redir_in_valor(t_general *g_data, char *line, int *redir, int i)
{
	if (line[i] == '>')
	{
		if (i > 1 && line[i - 1] == '>' && line[i - 2] == '>')
		{
			ft_putendl_fd(REDIR_ERROR_3, 1);
			g_data->status = 258;
			return (1);
		}
		if (line[i - 1] != '>')
			redir[0] = 3;
		else
			redir[0] = 4;
	}
	return (0);
}
