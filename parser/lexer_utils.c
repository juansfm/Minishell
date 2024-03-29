/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agil-ord <agil-ord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:47:55 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/02/01 15:01:03 by agil-ord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_pipes(char **input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (ft_strcmp(input[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

char	*ft_concatenate_strings(char *temp, char *input)
{
	char	*old_temp;
	size_t	temp_len;
	char	*result;

	old_temp = temp;
	temp_len = ft_strlen(temp) + ft_strlen(input) + 2;
	result = malloc(temp_len);
	ft_strlcpy(result, old_temp, temp_len);
	ft_strlcat(result, " ", temp_len);
	ft_strlcat(result, input, temp_len);
	free(old_temp);
	return (result);
}

char	**ft_concatenate_until_pipe(char **input)
{
	int		i;
	int		j;
	char	**result;
	char	*temp;

	result = malloc(sizeof(char *) * (ft_count_pipes(input) + 2));
	temp = ft_strdup("");
	i = 0;
	j = 0;
	while (input[i])
	{
		if (ft_strcmp(input[i], "|") != 0)
			temp = ft_concatenate_strings(temp, input[i]);
		else
		{
			result[j++] = temp;
			temp = ft_strdup("");
		}
		i++;
	}
	result[j++] = temp;
	result[j] = NULL;
	ft_free(input, ft_mtxrow(input));
	return (result);
}
