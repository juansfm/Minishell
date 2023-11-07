/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:44:57 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/11/06 18:07:21 by jsaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_l(void)
{
	system("leaks -q Minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_general	g_data;
	t_env		*temp;
	char		*line;
	char		**mtx;

	atexit(ft_l);
	(void)argc;
	(void)argv;
	ft_dup_env(&g_data, envp);
	while (1)
	{
		line = readline("Minishell$");
		printf("%s\n", line);
		if (line)
		{
			mtx = ft_env_split(line, ' ');
			ft_builtins(&g_data, mtx[0], mtx[1]);
		}
		free(line);
	}
	// rl_clear_history();
	temp = g_data.env;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->name, temp->valor);
		temp = temp->next;
	}
	printf("\n");
	ft_add_mod_env(&g_data, "US=Hola=Adios");
	ft_add_mod_env(&g_data, "USA");
	temp = g_data.env;
	// ft_print_env(g_data);
	printf("\n");
	ft_print_export(&g_data);
	printf("\n");
	ft_delete_env(&g_data, "US");
	// ft_print_env(g_data);
	printf("\n");
	// ft_print_export(g_data);
}
