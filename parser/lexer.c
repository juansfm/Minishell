#include "minishell.h"

void	ft_parse_tokens(t_general *g_data)
{
	char	current_char;
	int		pos;
	int		len;

	g_data->split_tokens = NULL;
	len = ft_strlen(g_data->cpy_line);
	pos = 0;
	while (pos < len)
	{
		current_char = g_data->cpy_line[pos];
		if (current_char == '\"' || current_char == '\'')
			ft_process_quote(g_data, &pos);
		pos++;
	}
	g_data->split_tokens = ft_tokenize(g_data);
	ft_funcion_junta_redirecciones(g_data);
	g_data->split_tokens = ft_eliminar_espacios(g_data->split_tokens);
	g_data->split_tokens = ft_concatenate_until_pipe(g_data->split_tokens);
}

void	ft_funcion_junta_redirecciones(t_general *g_data)
{
	int	i;
	int	j;

	i = 0;
	while (g_data->split_tokens[i] != NULL)
	{
		if ((ft_strcmp(g_data->split_tokens[i], "<") == 0
				|| ft_strcmp(g_data->split_tokens[i], ">") == 0)
			&& g_data->split_tokens[i + 1] != NULL)
		{
			if (ft_strcmp(g_data->split_tokens[i],
					g_data->split_tokens[i + 1]) == 0)
			{
				g_data->split_tokens[i] = ft_strjoin_free(g_data->split_tokens[i],
						g_data->split_tokens[i + 1]);
				j = i + 1;
				free(g_data->split_tokens[j]);
				while (g_data->split_tokens[j] != NULL)
				{
					g_data->split_tokens[j] = g_data->split_tokens[j + 1];
					j++;
				}
			}
		}
		i++;
	}
}

void	ft_parser(t_general *g_data, char *line)
{
	g_data->cpy_line = ft_strdup(line);
	ft_parse_tokens(g_data);
}

int	ft_solo_espacios(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			return (1);
		}
		i++;
	}
	return (0);
}
