#include "minishell.h"

void	ft_parse_tokens(t_general *g_data)//usado para hacer split primero
{
	char current_char;
	int pos;
    char **split_tokens = NULL;
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
                
                //ft_process_pipe_in_quote(g_data, &pos);
                //printf("\nla cadena tras pipe: %s\n", g_data->cpy_line);
                //ft_process_red_in_quote(g_data, &pos);
                //printf("\nla cadena tras red: %s\n", g_data->cpy_line);
                //ft_modify_string(g_data->cpy_line);
                //printf("\nla cadena tras modify: %s\n", g_data->cpy_line);
                // printf("pos despues es: %d\n", pos);
        }         
		pos++;
	}
    //printf("\033[0;31m");
    //printf("la cadena tras quote: %s\n", g_data->cpy_line);
    //printf("\033[0m");
    split_tokens = ft_tokenize(g_data, ft_strlen(g_data->cpy_line));
    while(split_tokens[i])
    {
        printf("\033[0;36m");
        printf("\nlokey first bucle: %s", split_tokens[i]);
        printf("\033[0m");
        i++;
    }
    //split_tokens = ft_split_modify(g_data->cpy_line, '|', split_tokens);
    printf("\033[0;32m");
    printf("\nla cadena tras split: %s", g_data->cpy_line);
    printf("\033[0m");
    split_tokens = ft_eliminar_espacios(split_tokens);
    //ft_limpiar_espacios(&split_tokens);
    i = 0;
    while(split_tokens[i])
    {
        ft_quitar_comillas(split_tokens[i]);
        printf("\033[0;30m");
        printf("\nla cadena tras limpiar espacios: %s", g_data->cpy_line);
        printf("\033[0m");
        i++;
    }
    //aqui llamo a la funcion que me expande las variables, ya que aun lo tengo en
    // cadenas mas pequeñas
    i = 0;
    while(split_tokens[i])
    {
        split_tokens[i] = funcion_que_lo_lleva_todo(g_data, split_tokens[i]);
        printf("\nesto es mirando si hay dolar: %s", split_tokens[i]);
        i++;
    }
    ft_restore_quotes(split_tokens);
    //funcion_expandir(t_general g_data, char **split_tokens);
}


void	ft_parser(t_general *g_data, char *line)
{
    g_data->cpy_line = ft_strdup(line);
    printf("\033[0;33m");
    printf("\nlinea copiada ft_parser: %s\n", g_data->cpy_line);
    printf("\033[0m");
    //printf("len: %d\n", len);
   // ft_inicializar_tokens(t_token *token);
    ft_parse_tokens(g_data);
    
    
    //hasta aqui tengo tokens con las palabras y los separadores
    //me falta expandir las variables $
    //quitar comillas y juntar palabras
    //juntar si hay mas de una redireccion del miso tipojuntar(al pasarlo a listas)


}
