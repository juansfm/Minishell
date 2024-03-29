/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:17:50 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/10/18 18:18:50 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_free(char **matrix, int j)
{
	while (j-- > 0)
		free(matrix[j]);
	free(matrix);
}
