#include "minishell.h"

void	ft_parse_tokens(t_general *g_data)//usado para hacer split primero
{
	char current_char;
	int pos;
    int i = 0;
    int len;
    len = ft_strlen(g_data->cpy_line);
	pos = 0;
   // start = pos;
	while(pos < len)
	{   
		current_char = g_data->cpy_line[pos];
		if (current_char == '\"' || current_char == '\'') 
        {
                //printf("pos antes comilla es: %d\n\n", pos);
                ft_process_quote(g_data, &pos);
                printf("\nla cadena tras quote: %s\n\n", g_data->cpy_line);
        }         
		pos++;
	}
    g_data->split_tokens = ft_tokenize(g_data, ft_strlen(g_data->cpy_line));
    i = 0;
    while(g_data->split_tokens[i])
    {
        printf("\033[0;32m");
        printf("\nla cadena tras separar en tokens: %s", g_data->split_tokens[i]);
        printf("\033[0m");
        i++;
    }
    ft_funcion_junta_redirecciones(g_data);
    g_data->split_tokens = ft_eliminar_espacios(g_data->split_tokens);
    g_data->split_tokens = ft_concatenate_until_pipe(g_data->split_tokens);
    
    i = 0;
    while(g_data->split_tokens[i])
    {
        //ft_quitar_comillas(g_data->split_tokens[i]);
        printf("\033[0;32m");
        printf("\nla cadena tras separar en comandos: %s", g_data->split_tokens[i]);
        printf("\033[0m");
        i++;
    }
}

void ft_funcion_junta_redirecciones(t_general *g_data)
{
    int i = 0;
    while (g_data->split_tokens[i] != NULL)
    {
        if ((ft_strcmp(g_data->split_tokens[i], "<") == 0 || ft_strcmp(g_data->split_tokens[i], ">") == 0) && g_data->split_tokens[i + 1] != NULL)
        {
            if (ft_strcmp(g_data->split_tokens[i], g_data->split_tokens[i + 1]) == 0)
            {
                // Combina las dos redirecciones en una
                g_data->split_tokens[i] = ft_strjoin(g_data->split_tokens[i], g_data->split_tokens[i + 1]);

                // Mueve el resto de las cadenas hacia abajo para eliminar la redirección duplicada
                int j = i + 1;
                while (g_data->split_tokens[j] != NULL)
                {
                    g_data->split_tokens[j] = g_data->split_tokens[j + 1];
                    j++;
                }
            }
        }
        i++;
    }
}


void	ft_parser(t_general *g_data, char *line)
{
    g_data->cpy_line = ft_strdup(line);
    /*printf("\033[0;33m");
    printf("\nlinea copiada ft_parser: %s\n", g_data->cpy_line);
    printf("\033[0m");
    //printf("len: %d\n", len);*/
   // ft_inicializar_tokens(t_token *token);
    ft_parse_tokens(g_data);
}
