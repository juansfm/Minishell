/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agil-ord <agil-ord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:48:12 by jsaavedr          #+#    #+#             */
/*   Updated: 2024/02/01 15:03:17 by agil-ord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig)
{
	if (SIGINT == sig && g_running == 3)
	{
		g_running = -3;
		rl_replace_line("", 0);
		ft_putstr_fd("   \n", 1);
	}
	else if (SIGINT == sig && g_running == 2)
	{
		g_running = -2;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
	else if (SIGINT == sig)
	{
		g_running = 1;
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		ft_putstr_fd("   \n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_ctrl_d(t_general *g_data)
{
	if (!g_data->cmd)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("exit\n", 1);
		rl_clear_history();
		ft_free_cmd(g_data);
		exit(EXIT_SUCCESS);
	}
}
