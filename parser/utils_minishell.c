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

char	**ft_convert_token_list_to_array(t_token *token_list)
{
	int		count;
	int		i;
	char	**array;
	t_token	*current;

	count = 0;
	current = token_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	array = ft_calloc(sizeof(char *), (count + 1));
	if (!array)
		return (NULL);
	current = token_list;
	i = 0;
	while (i < count)
	{
		array[i] = ft_strdup(current->value);
		current = current->next;
		i++;
	}
	array[count] = NULL;
	return (array);
}
