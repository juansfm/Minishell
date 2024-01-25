#include "minishell.h"
/*
static void	ft_ctrl_c(int signal)
{
	(void)signal;
	if (g_running == 0)
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		write(1, "\033[K\n", 5);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
	else if (g_running == 1)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
	}
}

void	ft_signals(void)
{
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}*/
void	ft_handler(int sig)
{
	if (SIGINT == sig)
	{
		g_running = 1;
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("   ", 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
	if (SIGQUIT == sig)
	{
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

/*void	ft_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (SIGINT == sig) // user press CTRL+C
	{
		g_listen = 1;
		rl_on_new_line();
		rl_redisplay();
	//	rl_replace_line("   ", 0);
		ft_putstr_fd("   ", 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n"); // 0 es STDIN_FILENO
		rl_on_new_line();
	//	rl_redisplay();
	}
//	else if (SIGSTOP == sig)
} 


 * @brief    **  IT'S NOT A SIGNAL, ONLY A SPECIAL CHARACTER **
 * 	-	rl_on_new_line(); // parece que limpia el búffer
 *	-	rl_redisplay();	// y parece que se pone al inicio de la misma línea
 * 
 * @param data 

void	ft_ctrl_d(t_msh *data)
{
	if (!data->pipeline)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("exit\n", 1);
		rl_clear_history();
		ft_env_lstclear(data->env_lst);
		exit(EXIT_SUCCESS); // te saca de minishell
	}
} */