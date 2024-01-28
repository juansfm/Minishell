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

char	*ft_process_word(t_general *g_data, char *extract_word,
		int *i, char *string_restruc)
{
	char	*word_exchange;

	if (ft_strcmp(extract_word, "?") == 0)
	{
		word_exchange = ft_itoa(g_data->status);
		string_restruc = ft_strjoin_free(string_restruc, word_exchange);
		free(word_exchange);
		(*i)++;
	}
	else if (!(*extract_word) || (ft_char_reserved(extract_word[0]) == 1))
	{
		string_restruc = ft_charjoin_free(string_restruc, '$');
		(*i)++;
	}
	else
	{
		word_exchange = ft_get_word_exchange(g_data, extract_word);
		string_restruc = ft_strjoin_free(string_restruc, word_exchange);
		(*i) += ft_strlen(extract_word);
		free(word_exchange);
	}
	return (string_restruc);
}

char	*ft_process_dollar(t_general *g_data, char *cmd,
			int *i, char *string_restruc)
{
	int		dollar_pos;
	char	*extract_word;

	dollar_pos = *i;
	extract_word = ft_extract_word(cmd, dollar_pos);
	(*i)++;
	string_restruc = ft_process_word(g_data, extract_word, i, string_restruc);
	free(extract_word);
	return (string_restruc);
}
