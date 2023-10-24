/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:38:00 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/10/16 13:41:53 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = ft_strlen(dst) + ft_strlen(src);
	if (ft_strlen(dst) >= dstsize)
		k = ft_strlen(src) + dstsize;
	while (dst[i] != '\0')
		i++;
	while (i + j < dstsize)
	{
		if (src[j] == '\0' || i + j == dstsize - 1)
		{
			dst[i + j] = '\0';
			break ;
		}
		dst[i + j] = src[j];
		j++;
	}
	return (k);
}
