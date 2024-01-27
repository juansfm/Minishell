/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:53:20 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/01/27 20:29:08 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		k;
	char	*str;

	if (!s1 || !s2)
		return (0);
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (str != NULL)
	{
		k = 0;
		while (s1[k] != '\0')
		{
			str[k] = s1[k];
			k++;
		}
		while (s2[k - ft_strlen(s1)] != '\0')
		{
			str[k] = s2[k - ft_strlen(s1)];
			k++;
		}
		return (str);
	}
	return (0);
}
