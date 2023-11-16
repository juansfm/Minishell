/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaavedr <jsaavedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:44:57 by jsaavedr          #+#    #+#             */
/*   Updated: 2023/11/16 13:10:21 by jsaavedr         ###   ########.fr       */
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
	char		*line;
	char		*line2;
	char		**mtx;

	// atexit(ft_l);
	(void)argc;
	(void)argv;
	ft_dup_env(&g_data, envp);
	while (1)
	{
		line = readline("Minishell$");
		// printf("%s\n", line);
		if (line)
		{
			line = ft_strtrim(line, " ");
			mtx = ft_env_split(line, ' ');
			line2 = ft_strdup(mtx[0]);
			// ft_free(mtx, ft_mtxrow(mtx));
			line = ft_strchr(line, ' ');
			line = ft_strtrim(line, " ");
			if (line != NULL)
				mtx = ft_split(line, ' ');
			else
				mtx = NULL;
			// if (mtx)
			// {
				// int i = -1;
				// while(mtx[++i])
				// printf("hola:%s\n", mtx[i]);
			// }
			ft_builtins(&g_data, line2, mtx);
			// free(line2);
			// ft_free(mtx, ft_mtxrow(mtx));
		}
	}
}
