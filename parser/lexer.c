#include "minishell.h"

int ft_process_quote_content_double(char *line, int len, int pos, t_token **head)
{
    char quote = line[pos];
    int start = pos + 1;
    int end = start;
    int j = 0;
    char *value = NULL;

    while (end < len && line[end] != quote)
        end++;
    if (end >= len)
    {
        printf("Error: No se encontró el cierre de las comillas.\n");
        exit(EXIT_FAILURE);
    }
    else 
    {
        value = malloc((end - start)+ 1);
        while (j < (end - start)) 
        {
            value[j] = line[start + j];
            j++;
        }
        value[end] = '\0';
        ft_add_token_in_general(head, TOKEN_WORD, value);
        free(value);
    }
    return pos;
}

int ft_process_quote_content_sim(char *line, int len, int pos, t_token **head)
{
    int start = pos + 1; //despues de quitar la comilla
    int end = start;
    int j = 0;
    char quote = line[pos]; //compruebo que es igual a la comilla llamada
    char *value = NULL;
    
    while ((end < len) && (line[end] != quote))
        end++;
    if (end > len)
    {
        printf("Error: No se encontró el cierre de las comillas.\n");
        exit(EXIT_FAILURE);
    }
    else 
    {
        value = malloc((end - start) + 1);
        while (j < (end - start)) 
        {
            value[j] = line[start + j];
            j++;
        }
        
        value[j] = '\0';
        ft_add_token_in_general(head, TOKEN_WORD, value);
        free(value);
    }
    pos = end;
    return pos; // Actualizar la posición
}

int ft_process_word(char *line, int len, int pos, t_token **head)
{
    int start = pos;
    int end = start;
    int j = 0;
    char *value = NULL;

    while (end < len && !ft_char_reserved(line[end]))
        end++;
    value = malloc(sizeof(char ) * ((end - start) + 1));
    while (j < (end - start)) 
    {
        value[j] = line[start + j];
        j++;
    }
    value[j] = '\0';
    ft_add_token_in_general(head, TOKEN_WORD, value);
    free(value);
    return (end - 1);
}

void	ft_parse_tokens(t_general *g_data)//usado para hacer split primero
{
	char current_char;
	int pos;
    char **split_tokens;
   // int start;
    // int i = 0;
    int len;

    len = ft_strlen(g_data->cpy_line);
	pos = 0;
   // start = pos;
	while(pos < len)
	{   
		current_char = g_data->cpy_line[pos];
		if (current_char == '\"' || current_char == '\'') 
        {
                printf("pos antes comilla es: %d\n", pos);
                ft_process_quote(g_data, &pos);
                printf("\nla cadena tras quote: %s\n", g_data->cpy_line);
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
    printf("la cadena tras quote: %s\n", g_data->cpy_line);
     split_tokens = ft_split(g_data->cpy_line, ' ');
     
     ft_restore_quotes(split_tokens);

  /*
    while (pos < len)
    {
        current_char = g_data->cpy_line[pos];
        if (current_char == ' ')
        {
           ft_añadir_comillas(g_data->cpy_line, &pos);
        }
        else if (current_char == '|')
        {
            
            pos++;
        }
        else if (current_char == '<')
        {
            ft_add_token_in_general(&g_data->token, TOKEN_LESS, NULL);
            pos++;
        }
        else if (current_char == '>')
        {
            ft_add_token_in_general(&g_data->token, TOKEN_GREAT, NULL);
            pos++;
        }
        else
        {
            pos = ft_process_word(g_data->cpy_line, len, pos, &g_data->token);
        }
    }
   // pos = start;
   // ft_modify_string(g_data->cpy_line);
    //ft_modify_string(g_data->cpy_line);
    split_tokens = ft_split(g_data->cpy_line, ' ');
    while(split_tokens[i])
    {
        printf("las palabras son: %s\n", split_tokens[i]);
        i++;
    }
  */  
}


void	ft_parser(t_general *g_data, char *line)
{
    g_data->cpy_line = ft_strdup(line);
    printf("linea copiada ft_parser: %s\n", g_data->cpy_line);
    //printf("len: %d\n", len);
   // ft_inicializar_tokens(t_token *token);
    ft_parse_tokens(g_data);
    //ft_print_tokens(g_data->token);
   // ft_free_tokens(g_data->token);
}
