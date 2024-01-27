#include "minishell.h"

int	ft_exist_valid_dollar(char *comand)
{
	int	i;
	int	quote_simple;
	int	quote_double;

	i = 0;
	quote_simple = 0;
	quote_double = 0;
	while (comand[i])
	{
		if (comand[i] == '\"')
			quote_double = (quote_double + 1) % 2;
		else if (comand[i] == '\'')
		{
			if (quote_double == 0)
				quote_simple = (quote_simple + 1) % 2;
		}
		else if (comand[i] == '$' && quote_simple == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_start_expand(t_general *g_data, t_cmd *cmd)
{
	int	i;
	int	pos;
	int	j;

	i = 0;
	pos = 0;
	j = 0;
	while (cmd->cmd[i])
	{
		if ((ft_exist_valid_dollar(cmd->cmd[i]) > -1))
			cmd->cmd[i] = ft_expand_all(g_data, cmd->cmd[i]);
		i++;
	}
}

char	*ft_get_word_exchange(t_general *g_data, char *dollar_word)
{
	t_env	*env;
	char	*word_exchange;

	if (ft_env_search(g_data, dollar_word))
	{
		env = ft_env_search(g_data, dollar_word);
		word_exchange = ft_strdup(env->value);
	}
	else
		word_exchange = ft_strdup("");
	return (word_exchange);
}


char	*ft_expand_all(t_general *g_data, char *cmd)
{
	int		dollar_pos;
	int		i;
	char	*string_restruc;
	char	*word_exchange;
	char	*extract_word;

	i = 0;
	dollar_pos = -1;
	string_restruc = ft_strdup("");
	word_exchange = NULL;
	while (cmd[i])
	{
		ft_if_is_quote(cmd[i], g_data);
		if (ft_char_is_dollar(cmd[i], g_data) == 0)
			dollar_pos = i;
		if (dollar_pos == -1)
		{
			string_restruc = ft_charjoin_free(string_restruc, cmd[i]);
			i++;
		}
		else
		{
			extract_word = ft_extract_word(cmd, dollar_pos);
			i++;
			if (ft_strcmp(extract_word, "?") == 0)
			{
				word_exchange = ft_itoa(g_data->status);
				string_restruc = ft_strjoin_free(string_restruc,
													word_exchange);
				free(word_exchange);
				i++;
			}
			else if (!(*extract_word)
					|| (ft_char_reserved(extract_word[0]) == 1))
			{
				string_restruc = ft_charjoin_free(string_restruc, '$');
				i++;
			}
			else
			{
				word_exchange = ft_get_word_exchange(g_data, extract_word);
				string_restruc = ft_strjoin_free(string_restruc, word_exchange);
				i += ft_strlen(extract_word);
				free(word_exchange);
			}
			free(extract_word);
		}
		dollar_pos = -1;
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
	if (str[dollar_pos + 1] == '?')
		fin = 1;
	while (str[end] && (fin == 0))
	{
		if (!ft_isalnum(str[end]))
		{
			end--;
			break ;
		}
		end++;
	}
	word = ft_substr(str, start + 1, end - start);
	return (word);
}
