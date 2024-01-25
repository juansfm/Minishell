#include "minishell.h"

char	*ft_extract_token(char *cpy_line, int start, int end)
{
	int		token_length;
	char	*token;
	int		i;

	token_length = end - start;
	token = ft_calloc((token_length + 1), sizeof(char));
	if (!token)
		return (NULL);
	i = 0;
	while (start < end)
		token[i++] = cpy_line[start++];
	token[i] = '\0';
	return (token);
}

int	ft_is_delimiter(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

char	**ft_tokenize(t_general *g_data)
{
	char	**tokens;
	int		i;
	int		count;
	int		start;

	count = 0;
	start = 0;
	i = -1;
	tokens = ft_calloc((ft_strlen(g_data->cpy_line) + 1), sizeof(char *));
	if (!tokens)
		exit(EXIT_FAILURE);
	while (g_data->cpy_line[++i])
	{
		if (ft_is_delimiter(g_data->cpy_line[i]))
		{
			if (i > start)
				tokens[count++] = ft_extract_token(g_data->cpy_line, start, i);
			tokens[count++] = ft_extract_token(g_data->cpy_line, i, i + 1);
			start = i + 1;
		}
	}
	if (i > start)
		tokens[count++] = ft_extract_token(g_data->cpy_line, start, i);
	tokens[count] = NULL;
	return (tokens);
}

int	ft_contar_cadenas_validas(char **cadena_de_cadenas)
{
	int	i;
	int	cantidad_cadenas;

	cantidad_cadenas = 0;
	i = 0;
	while (cadena_de_cadenas[i] != NULL)
	{
		if (ft_strcmp(cadena_de_cadenas[i], " ") != 0)
			cantidad_cadenas++;
		i++;
	}
	return (cantidad_cadenas);
}

void	ft_copiar_cadenas_no_vacias(char **cadena_de_cadenas, char **resultado)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cadena_de_cadenas[i] != NULL)
	{
		if (ft_strcmp(cadena_de_cadenas[i], " ") != 0)
			resultado[j++] = cadena_de_cadenas[i];
		else
			free(cadena_de_cadenas[i]);
		i++;
	}
	free(cadena_de_cadenas);
}

char	**ft_eliminar_espacios(char **cadena_de_cadenas)
{
	int		cantidad_cadenas;
	char	**resultado;

	cantidad_cadenas = ft_contar_cadenas_validas(cadena_de_cadenas);
	resultado = ft_calloc((cantidad_cadenas + 1), sizeof(char *));
	if (!resultado)
		return (NULL);
	ft_copiar_cadenas_no_vacias(cadena_de_cadenas, resultado);
	resultado[cantidad_cadenas] = NULL;
	return (resultado);
}
