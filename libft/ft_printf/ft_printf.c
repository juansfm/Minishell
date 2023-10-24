/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:09:29 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/10/18 16:54:41 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_select(args, str, i + 1, &len);
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}

void	ft_select(va_list args, const char *str, int i, int *len)
{
	if (str[i] == 'd' || str[i] == 'i')
		ft_putnbr(va_arg(args, int), len);
	else if (str[i] == 'c')
		ft_putchar(va_arg(args, int), len);
	else if (str[i] == 's')
		ft_putstr(va_arg(args, char *), len);
	else if (str[i] == 'p')
	{
		ft_putstr("0x", len);
		ft_putnbr_ba(va_arg(args, unsigned long long), "0123456789abcdef", len);
	}
	else if (str[i] == 'x')
		ft_putnbr_ba(va_arg(args, unsigned int), "0123456789abcdef", len);
	else if (str[i] == 'X')
		ft_putnbr_ba(va_arg(args, unsigned int), "0123456789ABCDEF", len);
	else if (str[i] == 'u')
		ft_putunbr(va_arg(args, unsigned int), len);
	else if (str[i] == '%')
		ft_putchar('%', len);
}

size_t	pr_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
