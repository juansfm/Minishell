#include "minishell.h"

int	ft_cmd_len(t_general *g_data)
{
	t_cmd	*temp;
	int		i;

	temp = g_data->cmd;
	i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
