#include "minishell.h"

void	ft_vamos_a_expandir(t_general *g_data)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (g_data->cmd->cmd[i])
	{
		if ((ft_encontrar_dolar(g_data->cmd->cmd[i], pos) > -1))
			g_data->cmd->cmd[i] = ft_expand_all(g_data,
					g_data->cmd->cmd[i]);
		i++;
	}
}

char	*ft_get_word_exchange(t_general *g_data, char *palabra_dolar)
{
	t_env	*env;
	char	*word_exchange;

	if (palabra_dolar[0] != '?')
	{
		if (ft_env_search(g_data, palabra_dolar))
		{
			env = ft_env_search(g_data, palabra_dolar);
			word_exchange = ft_strdup(env->valor);
		}
		else
			word_exchange = "";
	}
	else
		word_exchange = ft_itoa(g_data->status);
	return (word_exchange);
}

char	*ft_process_dolar(t_general *g_data, char *string_restruc,
		int pos_dolar, int *pos)
{
	char	*palabra_dolar;
	char	*word_exchange;

	palabra_dolar = ft_extract_word(string_restruc, pos_dolar, pos);
	if (palabra_dolar[0] == '\0')
		return (string_restruc);
	word_exchange = ft_get_word_exchange(g_data, palabra_dolar);
	string_restruc = ft_remodelar_cadena(string_restruc, palabra_dolar,
			word_exchange, pos_dolar);
	free(palabra_dolar);
	free(word_exchange);
	return (string_restruc);
}

char	*ft_expand_all(t_general *g_data, char *cmd)
{
	int		pos;
	int		pos_dolar;
	char	*string_restruc;

	pos = 0;
	string_restruc = cmd;
	pos_dolar = ft_encontrar_dolar(string_restruc, pos);
	while ((pos_dolar) >= 0)
	{
		string_restruc = ft_process_dolar(g_data, string_restruc, pos_dolar,
				&pos);
		pos = 0;
		pos_dolar = ft_encontrar_dolar(string_restruc, pos);
	}
	free(cmd);
	return (string_restruc);
}
/*
char	*ft_expand_all(t_general *g_data, char *cmd)
{
	int		pos;
	int		pos_dolar;
	char	*palabra_dolar;
	char	*word_exchange;
	char	*string_restruc;
	t_env	*env;

	pos = 0;
	pos_dolar = 0;
	palabra_dolar = NULL;
	word_exchange = NULL;
	string_restruc = cmd;
	env = NULL;
	while ((pos_dolar = ft_encontrar_dolar(string_restruc, pos)) >= 0)
	{
		palabra_dolar = ft_extract_word(string_restruc, pos_dolar,
				&pos);
		if (palabra_dolar[0] == '\0')
			return (string_restruc);
		{
			if (ft_env_search(g_data, palabra_dolar))
			{
				env = ft_env_search(g_data, palabra_dolar);
				ft_strdup(env->valor);
				word_exchange = ft_strdup(env->valor);
			}
			else
				word_exchange = "";
			string_restruc = ft_remodelar_cadena(string_restruc,
					palabra_dolar, word_exchange, pos_dolar);
		}
		pos = 0;
	}
	return (string_restruc);
}

*/