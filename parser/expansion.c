#include "minishell.h"

void ft_vamos_a_expandir(t_general *g_data)
{
	int i = 0;
	int pos = 0;
	int *todas_pos_dolar;
	int j;
//	int len = 0;

	j = 0;
	todas_pos_dolar = NULL;
	while(g_data->cmd->cmd[i])
	{
		if((ft_encontrar_dolar(g_data->cmd->cmd[i], pos) > -1))
		{
			g_data->cmd->cmd[i] = ft_funcion_que_lo_lleva_todo(g_data, g_data->cmd->cmd[i]);
		}
		i++;
			// 	printf("\nPre funcion que lo lleva todo: %s\n", g_data->cmd->cmd[i]);
            // 	g_data->cmd->cmd[i] = ft_funcion_que_lo_lleva_todo(g_data, g_data->cmd->cmd[i]);
	}			
//   	printf("\nPost funcion que lo lleva todo: %s\n", g_data->cmd->cmd[i]);
}

char *ft_funcion_que_lo_lleva_todo(t_general *g_data, char *cmd)//esta funcion la llamare mas veces por si hay mas dolar
{
    int pos = 0;
    int pos_dolar = 0;
    char *palabra_dolar = NULL;
    char *word_exchange = NULL;
    char *cadena_ya_reestructurada = cmd;

    t_env *env = NULL;

    while ((pos_dolar = ft_encontrar_dolar(cadena_ya_reestructurada, pos)) >= 0)
    {
        palabra_dolar = ft_extract_word(cadena_ya_reestructurada, pos_dolar, &pos);

        printf("\033[0;31m");
        printf("\nesta es la palabra que tiene el dolar: %s\n", palabra_dolar);
        printf("\033[0m");
        //llamo a la funcion que busca en el execve
        if(palabra_dolar[0] == '\0')
            return (cadena_ya_reestructurada);
        {
            if(ft_env_search(g_data, palabra_dolar))
            {
                env = ft_env_search(g_data, palabra_dolar);
                ft_strdup(env->valor);
                word_exchange = ft_strdup(env->valor);
            }
            else
                word_exchange = "";
            cadena_ya_reestructurada = ft_remodelar_cadena(cadena_ya_reestructurada, palabra_dolar, word_exchange, pos_dolar);

        }
    /*    printf("\033[0;35m");
        printf("\nla cadena ya reestructurada: %s\n", cadena_ya_reestructurada);
        printf("\033[0m");*/
        pos = 0;
    }
    return (cadena_ya_reestructurada);
}
