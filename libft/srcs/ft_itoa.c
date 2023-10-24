/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:28:28 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/10/16 13:41:53 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char			*ft_fill_str(char *str, unsigned int n, int len);
static unsigned int	ft_negative_numbers(int num, unsigned int *len, char *sign);

char	*ft_itoa(int num)
{
	unsigned int	n;
	unsigned int	len;
	unsigned int	i;
	char			sign;
	char			*str;

	sign = '+';
	len = 1;
	n = ft_negative_numbers(num, &len, &sign);
	i = n;
	while (i / 10 != 0)
	{
		len++;
		i = i / 10;
	}
	str = (char *)ft_calloc((len + 1), sizeof(char));
	if (str == NULL)
		return (0);
	if (sign == '-')
		str[0] = sign;
	str = ft_fill_str(str, n, len - 1);
	return (str);
}

static char	*ft_fill_str(char *str, unsigned int n, int len)
{
	int	i;
	int	j;

	i = len;
	if (str[0] == '-')
		j = 1;
	else
		j = 0;
	while (i >= j)
	{
		str[i] = n % 10 + '0';
		if (i > 0)
			n = n / 10;
		i--;
	}
	return (str);
}

static unsigned int	ft_negative_numbers(int num, unsigned int *len, char *sign)
{
	unsigned int	n;

	if (num < 0)
	{
		*sign = '-';
		*len = 2;
		n = -num;
	}
	else
		n = num;
	return (n);
}
