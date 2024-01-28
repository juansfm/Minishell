#include "minishell.h"

t_cmd	*ft_create_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	new_cmd->infile = 0;
	new_cmd->outfile = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	ft_eliminate_quote(t_cmd *cmd)
{
	t_process_data	p;

	p.cmd = cmd;
	p.i = 0;
	p.j = 0;
	p.k = 0;
	p.in_quotes = 0;
	p.quote_char = '\0';
	p.temp = NULL;
	while (p.cmd->cmd[p.i])
	{
		ft_process_token(&p);
		ft_replace_token_in_cmd(&p);
		p.i++;
		p.j = 0;
		p.k = 0;
	}
}
