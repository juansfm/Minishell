#include "minishell.h"

void	ft_parse_tokens(t_general *g_data)//usado para hacer split primero
{
	char current_char;
	int pos;
    //int i = 0;
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
    g_data->split_tokens = ft_eliminar_espacios(g_data->split_tokens);
    g_data->split_tokens = ft_concatenate_until_pipe(g_data->split_tokens);
    //ft_limpiar_espacios(&g_data->split_tokens);
    /*
    i = 0;
    while(g_data->split_tokens[i])
    {
        //ft_quitar_comillas(g_data->split_tokens[i]);
        printf("\033[0;32m");
        printf("\nla cadena tras limpiar espacios: %s", g_data->split_tokens[i]);
        printf("\033[0m");
        i++;
    }
    ft_restore_quotes(g_data->split_tokens);
    //aqui llamo a la funcion que me expande las variables, ya que aun lo tengo en
    // cadenas mas pequeñas
    i = 0;
    pos = 0;
    while(g_data->split_tokens[i])
    {
        while(ft_encontrar_dolar(*g_data->split_tokens, pos) > 0)
            g_data->split_tokens[i] = funcion_que_lo_lleva_todo(g_data, g_data->split_tokens[i]);
        printf("\nPost funcion que lo lleva todo: %s\n", g_data->split_tokens[i]);
        i++;
    }
    i = 0;
    while(g_data->split_tokens[i])
    {
        printf("\033[0;31m");
        printf("\nComprobacion final[%d] %s\n", i, g_data->split_tokens[i]);
        printf("\033[0m");
        i++;
    }
    */
    //funcion_expandir(t_general g_data, char **g_data->split_tokens);
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
    
    
    //hasta aqui tengo tokens con las palabras y los separadores
    //me falta expandir las variables $
    //quitar comillas y juntar palabras
    //juntar si hay mas de una redireccion del miso tipojuntar(al pasarlo a listas)


}
