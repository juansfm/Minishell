#include "minishell.h"

int	ft_char_reserved(char c)
{
	if (c == ' ' || c == '|' || c == '>' || c == '<' || c == '\"' || c == '\'')
		return (1);
	return (0);
}

void	ft_print_tokens(t_token *head)
{
	while (head != NULL)
	{
		printf("Token Type: %d, Value: %s\n", head->type_token, head->value);
		head = head->next;
	}
}
