/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:15:07 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/10/18 16:57:00 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putchar(char c, int *len)
{
	write(1, &c, 1);
	*len = *len + 1;
}

void	ft_putstr(char *str, int *len)
{
	int	i;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		*len = *len + 6;
		return ;
	}
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i], len);
		i++;
	}
}

void	ft_putnbr(int n, int *len)
{
	if (n == -2147483648)
	{
		write(1, &"-", 1);
		write(1, "2147483648", 10);
		*len = *len + 11;
		return ;
	}
	if (n < 0 && n != -2147483648)
	{
		write(1, &"-", 1);
		n = -n;
		*len = *len + 1;
	}
	if (n > 9)
		ft_putnbr(n / 10, len);
	ft_putchar('0' + n % 10, len);
}

void	ft_putnbr_ba(unsigned long long nbr, char *base, int *length)
{
	unsigned int	i;
	unsigned int	len;

	len = pr_strlen(base);
	if (nbr >= len)
		ft_putnbr_ba(nbr / len, base, length);
	i = nbr % len;
	write(1, &base[i], 1);
	*length += 1;
	return ;
}

void	ft_putunbr(unsigned int unbr, int *len)
{
	if (unbr > 9)
		ft_putunbr(unbr / 10, len);
	ft_putchar('0' + unbr % 10, len);
}