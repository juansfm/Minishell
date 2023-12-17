#include "minishell.h"

void	ft_signals(void)
{
	signal(SIGINT, ctr_c);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_ctr_c(int signal)
{
	(void)signal;
	if (!g_data.line)
		ioctl(0, TIOCSTI, "\n");
	else
		write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
}