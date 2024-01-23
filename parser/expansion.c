#include "minishell.h"

void	ft_vamos_a_expandir(t_general *g_data)
{
	int	i;
	int	pos;
	int	*todas_pos_dolar;
	int	j;

	i = 0;
	pos = 0;
	j = 0;
	todas_pos_dolar = NULL;
	while (g_data->cmd->cmd[i])
	{
		if ((ft_encontrar_dolar(g_data->cmd->cmd[i], pos) > -1))
			g_data->cmd->cmd[i] = ft_funcion_que_lo_lleva_todo(g_data,
					g_data->cmd->cmd[i]);
		i++;
	}
}

char	*ft_funcion_que_lo_lleva_todo(t_general *g_data, char *cmd)
{
	int		pos;
	int		pos_dolar;
	char	*palabra_dolar;
	char	*word_exchange;
	char	*cadena_ya_reestructurada;
	t_env	*env;

	pos = 0;
	pos_dolar = 0;
	palabra_dolar = NULL;
	word_exchange = NULL;
	cadena_ya_reestructurada = cmd;
	env = NULL;
	while ((pos_dolar = ft_encontrar_dolar(cadena_ya_reestructurada, pos)) >= 0)
	{
		palabra_dolar = ft_extract_word(cadena_ya_reestructurada, pos_dolar,
				&pos);
		if (palabra_dolar[0] == '\0')
			return (cadena_ya_reestructurada);
		{
			if (ft_env_search(g_data, palabra_dolar))
			{
				env = ft_env_search(g_data, palabra_dolar);
				ft_strdup(env->valor);
				word_exchange = ft_strdup(env->valor);
			}
			else
				word_exchange = "";
			cadena_ya_reestructurada = ft_remodelar_cadena(cadena_ya_reestructurada,
					palabra_dolar, word_exchange, pos_dolar);
		}
		pos = 0;
	}
	return (cadena_ya_reestructurada);
}
