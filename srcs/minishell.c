/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:44:57 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/10/22 19:15:56 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*temp;
	char	*line;

	(void)argc;
	(void)argv;
	ft_dup_env(envp);
	while (1)
	{
		line = readline("Minishell////");
		printf("%s\n", line);
		if (!ft_strncmp(line, "exit", ft_strlen(line)))
			break ;
	}
	temp = g_data.env;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->name, temp->valor);
		temp = temp->next;
	}
	printf("\n");
	ft_add_mod_env("US=Hola=Adios");
	ft_add_mod_env("USA");
	temp = g_data.env;
	// ft_print_env();
	printf("\n");
	ft_print_export();
	printf("\n");
	ft_delete_env("US");
	// ft_print_env();
	printf("\n");
	// ft_print_export();
}
