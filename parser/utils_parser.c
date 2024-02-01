/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:48:27 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/01/28 16:48:28 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_char_reserved(char c)
{
	if (c == ' ' || c == '|' || c == '>' || c == '<' || c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	ft_replace_special_chars(t_general *g_data, int *pos, char current_char,
		int *count_quotes)
{
	while (g_data->cpy_line[*pos] && ((*count_quotes % 2 != 0)
			|| (*count_quotes == 0)))
	{
		if (g_data->cpy_line[*pos] == ' ')
			g_data->cpy_line[*pos] = '\1';
		else if (g_data->cpy_line[*pos] == '|')
			g_data->cpy_line[*pos] = '\2';
		else if (g_data->cpy_line[*pos] == '>')
			g_data->cpy_line[*pos] = '\3';
		else if (g_data->cpy_line[*pos] == '<')
			g_data->cpy_line[*pos] = '\4';
		else if (g_data->cpy_line[*pos] == current_char)
			(*count_quotes)++;
		(*pos)++;
	}
}

void	ft_process_quote(t_general *g_data, int *pos)
{
	char	current_char;
	int		count_quotes;

	count_quotes = 0;
	current_char = g_data->cpy_line[*pos];
	ft_replace_special_chars(g_data, pos, current_char, &count_quotes);
	*(pos) = *(pos)-1;
}

void	ft_restore_quotes(char **split_tokens)
{
	int	i;
	int	j;

	i = 0;
	while (split_tokens[i])
	{
		j = 0;
		while (split_tokens[i][j])
		{
			if (split_tokens[i][j] == '\1')
				split_tokens[i][j] = ' ';
			else if (split_tokens[i][j] == '\2')
				split_tokens[i][j] = '|';
			else if (split_tokens[i][j] == '\3')
				split_tokens[i][j] = '>';
			else if (split_tokens[i][j] == '\4')
				split_tokens[i][j] = '<';
			j++;
		}
		i++;
	}
}
