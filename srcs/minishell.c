#include "minishell.h"

t_cmd	*ft_cmd_last(t_general *g_data)
{
	t_cmd	*temp;

	temp = g_data->cmd;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}
void	ft_cmd_add_back(t_general *g_data, t_cmd *new)
{
	t_cmd	*temp;

	if (g_data->cmd == NULL)
		g_data->cmd = new;
	else
	{
		temp = ft_cmd_last(g_data);
		temp->next = new;
	}
}
t_cmd	*ft_cmd_new(char *arg)
{
	t_cmd	*cmd;
	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->cmd = ft_split(arg, ' ');
	cmd->infile = 0;
	cmd->outfile = 1;
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	cmd->next = NULL;
	return (cmd);
}

void ft_print_commands(t_cmd *cmd)
{
    t_cmd *current = cmd;
    int i = 0;

    while (current != NULL)
	{
        printf("Command group %d:\n", i);
        char **temp = current->cmd;
        while (*temp)
		{
            printf("(%s)\n", *temp);
            temp++;
        }
        current = current->next;
        i++;
    }
}
/* nuevo creo que desecho
void ft_cmd_lst(t_general *g_data)
{
    t_cmd *cmd;
    t_token *current_token = g_data->token;
    int i = 0;

    while (current_token && current_token->type_token != TOKEN_PIPE)
    {
        cmd = ft_cmd_new(current_token->value);
        ft_cmd_add_back(g_data, cmd);
        current_token = current_token->next;
        i++;
    }

    // Si encontramos un pipe, avanzamos al siguiente token
    if (current_token && current_token->type_token == TOKEN_PIPE)
    {
        g_data->token = current_token->next;
    }
}
*/
//antiguo(de juan)
void	ft_cmd_lst(t_general *g_data, char **mtx)
{
	t_cmd	*cmd;
	t_cmd	*temp;
	int		i;

	temp = g_data->cmd;
	i = -1;
	while (mtx[++i])
	{
		cmd = ft_cmd_new(mtx[i]);
		ft_cmd_add_back(g_data, cmd);
	}
}

void	ft_free_cmd(t_general *g_data)
{
	t_cmd	*temp;

	while (g_data->cmd != NULL)
	{
		temp = g_data->cmd;
		g_data->cmd = g_data->cmd->next;
		ft_free(temp->cmd, ft_mtxrow(temp->cmd));
		free(temp);
	}
}

void	ft_l(void)
{
	system("leaks -q Minishell");
}


void	ft_minish(char **envp)
{
	t_general	g_data;
	char		*line;
	//char		**mtx;
	g_running = 1;
	g_data.token = NULL;
	g_data.cmd = NULL;
	//atexit(ft_l);
	ft_dup_env(&g_data, envp);
	while (g_running)
	{
		line = readline("\033[0;32mMinishell$ \033[0m");
		if (!line || line[0] == '\0')
		{
			printf("\nSe ha ejecutado solo un enter\n");
			continue; // Salir si se presiona Ctrl+D o solo se da enter
		}
		if(line && *line)
			add_history(line);
			
		ft_parser(&g_data, line);
		//ft_print_tokens(g_data.token);
		ft_cmd_lst(&g_data, g_data.split_tokens);
		//ft_print_commands(g_data.cmd);
		ft_vamos_a_expandir(&g_data);
		
		//ft_restore_quotes(g_data.cmd->cmd);
		if (!ft_builtins(&g_data, g_data.cmd->cmd))
			ft_other_cmd(&g_data, g_data.cmd->cmd);
		free(line);
		ft_free_cmd(&g_data);
	}
	// rl_clear_history();
	//temp = g_data.env;
	
	// while (temp != NULL)
	// {
	// 	printf("%s=%s\n", temp->name, temp->valor);
	// 	temp = temp->next;
	// }
	printf("\n");
	//temp = g_data.env;

}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	//signal(SIGINT, ft_sigintHandler);
	if (argc == 1)
	{
		using_history();
		ft_minish(envp);
	}
	else
		printf("Error: too many arguments\n");
	return (0);
}

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
        	// while(ft_encontrar_dolar(g_data->cmd->cmd[i], pos) > 0)
			// {

			// }
			// 	printf("\nPre funcion que lo lleva todo: %s\n", g_data->cmd->cmd[i]);
            // 	g_data->cmd->cmd[i] = ft_funcion_que_lo_lleva_todo(g_data, g_data->cmd->cmd[i]);
	}			
   	printf("\nPost funcion que lo lleva todo: %s\n", g_data->cmd->cmd[i]);
}

/*
		printf("\nLa cadena que tiene el dolar es: %s\n", g_data->cmd->cmd[i]);
				todas_pos_dolar = ft_realloc(todas_pos_dolar, (sizeof (int)) * j, (sizeof (int)) * (j + 1));
		
				todas_pos_dolar[j] = ft_encontrar_dolar(g_data->cmd->cmd[i], pos);
				pos = todas_pos_dolar[j] + 1;
				j++;
			}
			ft_la_funcion_que_lo_lleva_todo(g_data, g_data->cmd->cmd[i]);
		}
		printf("\n HOLA CARACOLA\n");
		len = ft_strlen(g_data->cmd->cmd[i]);
			printf("\nLa cadena que tiene el dolar es: %s\n", g_data->cmd->cmd[i]);
	
			todas_pos_dolar[j] = ft_encontrar_dolar(g_data->cmd->cmd[i], pos);
			pos = todas_pos_dolar[j] + 1;
			j++;
		j = 0;
		while(todas_pos_dolar[j])
		{
			printf("\nLa pos de dolar rd: %d\n", todas_pos_dolar[j]);
			j++;
		}
		break;
		i++;
	while (todas_pos_dolar[j] != 0)
	 {
	 	ft_extract_word(g_data->cmd->cmd[i], todas_pos_dolar[j], todas_pos_dolar[j + 1]);
			
		g_data->cmd->cmd[i] = ft_funcion_que_lo_lleva_todo(g_data, g_data->cmd->cmd[i], todas_pos_dolar, &j);
	}
	 free(todas_pos_dolar);
    /i++;
ft_expand_correct(t_general *g_data)
{
	char **temp;
	int i;
	int j;
	int pos_dolar;
	char *palabra_dolar;

	temp = g_data->cmd->cmd;
	i = 0;
	j = 0;
	while(temp[i])
	{
		if(ft_encontrar_dolar(temp[i], j) > -1)
		{
			while(1)
			{
				pos_dolar = ft_encontrar_dolar(temp[i], j);
				palabra_dolar = ft_extract_word(temp[i], pos_dolar, &j);
				if (temp[j] == '\0')
					break;
				
				
			}
				//dar posicion del dolar
				//extraer palabra del dolar
				//enviar palabra el excuve
				//recibir el puntero y convertirlo a la palabra
				//reemplazar la palabra por la palabra si existe, si no existe modificar la cadena para que desaparzca $ y la palabra que hemos enviamos al excuve
				//
				//ft_expandir(g_data, temp->cmd[i]);
		}
	}

}
*/
/*
void ft_vamos_a_expandir(t_general *g_data)
{
	int i = 0;
	int pos = 0;
	int *todas_pos_dolar;
	int j;
	int len = 0;

	j = 0;
	todas_pos_dolar = NULL;
	while(g_data->cmd->cmd[i])
    {
		printf("\n HOLA CARACOLA\n");
		len = ft_strlen(g_data->cmd->cmd[i]);
		while(pos < len && (ft_encontrar_dolar(g_data->cmd->cmd[i], pos) > -1))
		{
			printf("\nLa cadena que tiene el dolar es: %s\n", g_data->cmd->cmd[i]);
			todas_pos_dolar = ft_realloc(todas_pos_dolar, (sizeof (int)) * j, (sizeof (int)) * (j + 1));
	
			todas_pos_dolar[j] = ft_encontrar_dolar(g_data->cmd->cmd[i], pos);
			pos = todas_pos_dolar[j] + 1;
			j++;
		}
		j = 0;
		while(todas_pos_dolar[j])
		{
			printf("\nLa pos de dolar rd: %d\n", todas_pos_dolar[j]);
			j++;
		}
		break;
		i++;
		//while (todas_pos_dolar[j] != 0)
		// {
		// 	ft_extract_word(g_data->cmd->cmd[i], todas_pos_dolar[j], todas_pos_dolar[j + 1]);
			
		// 	//g_data->cmd->cmd[i] = ft_funcion_que_lo_lleva_todo(g_data, g_data->cmd->cmd[i], todas_pos_dolar, &j);
		// }
		// free(todas_pos_dolar);
    	// i++;
    }	
        	// while(ft_encontrar_dolar(g_data->cmd->cmd[i], pos) > 0)
			// {

			// }
			// 	printf("\nPre funcion que lo lleva todo: %s\n", g_data->cmd->cmd[i]);
            // 	g_data->cmd->cmd[i] = ft_funcion_que_lo_lleva_todo(g_data, g_data->cmd->cmd[i]);
				
        	printf("\nPost funcion que lo lleva todo: %s\n", g_data->cmd->cmd[i]);
}
*/
/*
void ft_vamos_a_expandir(t_general *g_data)
{
    int i = 0;
    int pos = 0;
    int pos_dolar = 0;
    char *palabra_dolar = NULL;
    char *word_exchange = NULL;

    while(g_data->cmd->cmd[i])
    {
        pos = 0;
        while (1) {
            pos_dolar = ft_encontrar_dolar(g_data->cmd->cmd[i], pos);
            if(pos_dolar < 0)
                break;
            palabra_dolar = ft_extract_word(g_data->cmd->cmd[i], pos_dolar, &pos);
			printf("\nLa palabra que tiene el dolar es: %s\n", palabra_dolar);
            // Aquí debes obtener el valor de la variable de entorno palabra_dolar
            // word_exchange = obtener_valor_variable_entorno(palabra_dolar);
            g_data->cmd->cmd[i] = ft_remodelar_cadena(g_data->cmd->cmd[i], palabra_dolar, word_exchange, pos_dolar);
        }
        i++;
    }
}
*/

/*
//ls "aaa aa"|grep "a a">"asd"
void ft_syntaxis_error(t_general g_data, char *line)
{

}
*/

//otra cosa es que debo separar los comandos por pipes
//luego tengo que tener en cuenta las redirecciones
//porque si las hubieses tendria que modificar el orden de los valores del comando
//HAcer funcion que me separe los comandos por pipes y me junte los comandos como si fueran frase
//es decir split por pipes y juntar distintos nodos de la lista tokens para convertirlos en t_cmd