/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:26:50 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/10/22 14:16:32 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_num_words(const char *str, char c);
static int	ft_size_word(const char *str, int i, char c);

char	**ft_split(char const *str, char c)
{
	int		i;
	int		j;
	int		num_lines;
	char	**matrix;
	int		len_word;

	i = 0;
	j = 0;
	num_lines = ft_num_words(str, c);
	matrix = (char **)ft_calloc((num_lines + 1), sizeof(char *));
	if (matrix == NULL)
		return (NULL);
	while (i < num_lines)
	{
		while (str[j] == c)
			j++;
		len_word = ft_size_word(str, j, c);
		matrix[i] = ft_substr(str, j, len_word);
		if (matrix[i] == NULL)
			return (ft_free(matrix, i), NULL);
		j += len_word;
		i++;
	}
	return (matrix);
}

static int	ft_num_words(const char *str, char c)

{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			num++;
			while (str[i] != c && str[i])
				i++;
		}
		else
			i++;
	}
	return (num);
}

static int	ft_size_word(const char *str, int i, char c)
{
	int	size;

	size = 0;
	while (str[i] != c && str[i])
	{
		size++;
		i++;
	}
	return (size);
}
