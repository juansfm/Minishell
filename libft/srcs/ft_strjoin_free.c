/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:05:39 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/01/23 16:16:10 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = ft_calloc((i + j + 1), sizeof(char));
	if (str != NULL)
	{
		k = 0;
		while (s1[k] != '\0')
		{
			str[k] = s1[k];
			k++;
		}
		while (s2[k - i] != '\0')
		{
			str[k] = s2[k - i];
			k++;
		}
		free(s1);
		return (&str[0]);
	}
	return (0);
}
