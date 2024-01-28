#include "minishell.h"

char	*ft_charjoin_free(char *s1, char s2)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = ft_strlen(s1);
	j = 1;
	str = ft_calloc((i + j + 1), sizeof(char));
	if (str != NULL)
	{
		k = 0;
		while (s1[k] != '\0')
		{
			str[k] = s1[k];
			k++;
		}
		str[k] = s2;
		free(s1);
		return (&str[0]);
	}
	return (0);
}

void	ft_if_is_quote(char char_cmd, t_general *g_data)
{
	int	i;

	i = 0;
	if (char_cmd == '\"' && g_data->quote_double == 0
		&& g_data->quote_simple == 0)
		g_data->quote_double = 1;
	else if (char_cmd == '\'' && g_data->quote_double == 0
		&& g_data->quote_simple == 0)
		g_data->quote_simple = 1;
	else if (char_cmd == '\"' && g_data->quote_double == 1)
		g_data->quote_double = 0;
	else if (char_cmd == '\'' && g_data->quote_simple == 1)
		g_data->quote_simple = 0;
}

int	ft_char_is_dollar(char cmd_char, t_general *g_data)
{
	if (cmd_char == '$' && g_data->quote_simple == 0)
		return (0);
	return (-1);
}

char	*ft_cpy_part(char *str, int *pos, int num_chars)
{
	int		start;
	char	*dest;

	start = *pos;
	if (num_chars > 0)
		dest = ft_substr(str, start, num_chars);
	else
		dest = ft_strdup("");
	*pos = start + num_chars;
	return (dest);
}

int	ft_is_delimiter(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
