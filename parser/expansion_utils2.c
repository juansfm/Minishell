#include "minishell.h"

char	*ft_process_no_dollar(char *cmd, int *i, char *string_restruc)
{
	string_restruc = ft_charjoin_free(string_restruc, cmd[*i]);
	(*i)++;
	return (string_restruc);
}

char	*ft_expand_all(t_general *g_data, char *cmd)
{
	int		i;
	char	*string_restruc;

	i = 0;
	string_restruc = ft_strdup("");
	while (cmd[i])
	{
		ft_if_is_quote(cmd[i], g_data);
		if (ft_char_is_dollar(cmd[i], g_data) == 0)
			string_restruc = ft_process_dollar(g_data, cmd, &i, string_restruc);
		else
			string_restruc = ft_process_no_dollar(cmd, &i, string_restruc);
	}
	g_data->quote_double = 0;
	g_data->quote_simple = 0;
	free(cmd);
	return (string_restruc);
}

char	*ft_extract_word(char *str, int dollar_pos)
{
	int		start;
	int		end;
	char	*word;
	int		fin;

	word = NULL;
	fin = 0;
	start = dollar_pos;
	end = start + 1;
	if (str[end] && ft_isdigit(str[end]))
		fin = 1;
	if (str[dollar_pos + 1] == '?' || str[dollar_pos + 1] == '_')
		fin = 1;
	while (str[end] && (fin == 0))
	{
		if (!ft_isalnum(str[end]) && str[end] != '_')
		{
			end--;
			break ;
		}
		end++;
	}
	word = ft_substr(str, start + 1, end - start);
	return (word);
}
