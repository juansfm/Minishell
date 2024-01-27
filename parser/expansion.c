#include "minishell.h"

void	ft_entrecomillas(char char_cmd, t_general *g_data)
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

int	ft_existe_dolar_valido(char *comand)
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

void	ft_vamos_a_expandir(t_general *g_data, t_cmd *cmd)
{
	int	i;
	int	pos;
	int	j;

	i = 0;
	pos = 0;
	j = 0;
	while (cmd->cmd[i])
	{
		if ((ft_existe_dolar_valido(cmd->cmd[i]) > -1))
			cmd->cmd[i] = ft_expand_all(g_data, cmd->cmd[i]);
		i++;
	}
}

char	*ft_get_word_exchange(t_general *g_data, char *palabra_dolar)
{
	t_env	*env;
	char	*word_exchange;

	if (ft_env_search(g_data, palabra_dolar))
	{
		env = ft_env_search(g_data, palabra_dolar);
		word_exchange = ft_strdup(env->valor);
	}
	else
		word_exchange = ft_strdup("");
	return (word_exchange);
}

int	ft_comprobar_dolar(char cmd_char, t_general *g_data)
{
	if (cmd_char == '$' && g_data->quote_simple == 0)
		return (0);
	return (-1);
}

char	*ft_expand_all(t_general *g_data, char *cmd)
{
	int		pos_dolar;
	int		i;
	char	*string_restruc;
	char	*word_exchange;
	char	*palabra_extraida;

	i = 0;
	pos_dolar = -1;
	string_restruc = ft_strdup("");
	word_exchange = NULL;
	while (cmd[i])
	{
		ft_entrecomillas(cmd[i], g_data);
		if (ft_comprobar_dolar(cmd[i], g_data) == 0)
			pos_dolar = i;
		printf("\npos_dolar: %d\n", pos_dolar);
		if (pos_dolar == -1)
		{
			string_restruc = ft_charjoin_free(string_restruc, cmd[i]);
			printf("\nstring_restruc: %s\n", string_restruc);
			i++;
		}
		else
		{
			palabra_extraida = ft_extract_word(cmd, pos_dolar);
			i++;
			printf("\npalabra_extraida: %s\n", palabra_extraida);
			if (ft_strcmp(palabra_extraida, "?") == 0)
			{
				printf("\nstatus: %d\n", g_data->status);
				word_exchange = ft_itoa(g_data->status);
				string_restruc = ft_strjoin_free(string_restruc,
													word_exchange);
				free(word_exchange);
				i++;
			}
			else if (!(*palabra_extraida)
					|| (ft_char_reserved(palabra_extraida[0]) == 1))
			{
				string_restruc = ft_charjoin_free(string_restruc, '$');
				i++;
			}
			else
			{
				word_exchange = ft_get_word_exchange(g_data, palabra_extraida);
				string_restruc = ft_strjoin_free(string_restruc, word_exchange);
				i += ft_strlen(palabra_extraida);
				free(word_exchange);
			}
			free(palabra_extraida);
		}
		pos_dolar = -1;
	}
	g_data->quote_double = 0;
	g_data->quote_simple = 0;
	free(cmd);
	return (string_restruc);
}

char	*ft_extract_word(char *str, int pos_dolar)
{
	int		start;
	int		end;
	char	*word;
	int		fin;

	word = NULL;
	fin = 0;
	start = pos_dolar;
	end = start + 1;
	if (str[end] && ft_isdigit(str[end]))
		fin = 1;
	if (str[pos_dolar + 1] == '?')
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
