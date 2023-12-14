#include "minishell.h"

int	ft_process_quote_content_double(char *line, int len, int pos,
		t_token **head)
{
	char	quote;
	int		start;
	int		end;
	int		j;
	char	*value;

	quote = line[pos];
	start = pos + 1;
	end = start;
	j = 0;
	value = NULL;
	while (end < len && line[end] != quote)
		end++;
	if (end >= len)
	{
		printf("Error: No se encontró el cierre de las comillas.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		value = malloc((end - start) + 1);
		while (j < (end - start))
		{
			value[j] = line[start + j];
			j++;
		}
		value[end] = '\0';
		ft_add_token_in_general(head, TOKEN_WORD, value);
		free(value);
	}
	return (pos);
}

int	ft_process_quote_content_sim(char *line, int len, int pos, t_token **head)
{
	int		end;
	int		j;
	char	*value;

	int start = pos + 1; //despues de quitar la comilla
	end = start;
	j = 0;
	char quote = line[pos]; //compruebo que es igual a la comilla llamada
	value = NULL;
	while ((end < len) && (line[end] != quote))
		end++;
	if (end > len)
	{
		printf("Error: No se encontró el cierre de las comillas.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		value = malloc((end - start) + 1);
		while (j < (end - start))
		{
			value[j] = line[start + j];
			j++;
		}
		value[j] = '\0';
		printf("el valor es %s\n", value);
		printf("la pos es %d\n", end);
		ft_add_token_in_general(head, TOKEN_WORD, value);
		free(value);
	}
	pos = end;
	return (pos); // Actualizar la posición
}

int	ft_process_word(char *line, int len, int pos, t_token **head)
{
	int		start;
	int		end;
	int		j;
	char	*value;

	start = pos;
	end = start;
	j = 0;
	value = NULL;
	while (end < len && !ft_char_reserved(line[end]))
		end++;
	value = malloc(sizeof(char) * ((end - start) + 1));
	while (j < (end - start))
	{
		value[j] = line[start + j];
		j++;
	}
	value[j] = '\0';
	ft_add_token_in_general(head, TOKEN_WORD, value);
	free(value);
	return (end - 1);
}

void	ft_parse_tokens(char *line, int len, t_general **g_data)
{
	char	current_char;
	int		pos;

	pos = 0;
	while (pos < len)
	{
		current_char = line[pos];
		if (current_char == '\"' || current_char == '\'')
		{
			if (current_char == '\"')
				pos = ft_process_quote_content_double(line, len, pos,
						&(*g_data)->token);
			else
			{
				pos = ft_process_quote_content_sim(line, len, pos,
						&(*g_data)->token);
				printf("la pos es: %d\n", pos);
			}
		}
		else if (current_char == '|')
			ft_add_token_in_general(&(*g_data)->token, TOKEN_PIPE, "|");
		//else if(current_char == '$')
		//	ft_add_token_in_general(head, TOKEN_DOLLAR, value);
		else if (current_char == '>')
			ft_add_token_in_general(&(*g_data)->token, TOKEN_WORD, ">");
		else if (current_char == '<')
			ft_add_token_in_general(&(*g_data)->token, TOKEN_WORD, "<");
		else
			pos = ft_process_word(line, len, pos, &(*g_data)->token);
		pos++;
	}
}

void	ft_parser(t_general *g_data, char *line)
{
	int	len;

	len = ft_strlen(line);
	// ft_inicializar_tokens(t_token *token);
	ft_parse_tokens(line, len, &g_data);
	ft_print_tokens(g_data->token);
	ft_free_tokens(g_data->token);
}
