/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:26 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/10/22 19:33:16 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char *env_line)
{
	t_env	*temp;

	temp = ft_env_new(env_line);
	if (!env_line)
		ft_print_export();
	if (ft_env_error(temp->name))
	{
		ft_free_env(temp);
		return ;
	}
	ft_free_env(temp);
	ft_add_mod_env(env_line);
}
