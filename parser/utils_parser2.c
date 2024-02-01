/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agil-ord <agil-ord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:48:30 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/02/01 15:45:44 by agil-ord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (NULL);
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

int	ft_count_valid_strings(char **string_of_strings)
{
	int	i;
	int	num_of_strings;

	num_of_strings = 0;
	i = 0;
	while (string_of_strings[i] != NULL)
	{
		if (ft_strcmp(string_of_strings[i], " ") != 0)
			num_of_strings++;
		i++;
	}
	return (num_of_strings);
}

void	ft_cpy_string_void(char **string_of_strings, char **resultado)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (string_of_strings[i] != NULL)
	{
		if (ft_strcmp(string_of_strings[i], " ") != 0)
			resultado[j++] = string_of_strings[i];
		else
			free(string_of_strings[i]);
		i++;
	}
	free(string_of_strings);
}

char	**ft_clean_spaces(char **string_of_strings)
{
	int		num_of_strings;
	char	**resultado;

	num_of_strings = ft_count_valid_strings(string_of_strings);
	resultado = ft_calloc((num_of_strings + 1), sizeof(char *));
	if (!resultado)
		return (NULL);
	ft_cpy_string_void(string_of_strings, resultado);
	resultado[num_of_strings] = NULL;
	return (resultado);
}
