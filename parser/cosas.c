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

char *funcion_que_lo_lleva_todo(t_general *g_data, char *split_tokens)//esta funcion la llamare mas veces por si hay mas dolar
{
    int pos = 0;
    int pos_dolar = 0;
    char *palabra_dolar = NULL;
    char *word_exchange = NULL;
    char *cadena_ya_reestructurada = NULL;
    g_data = NULL;

    while(pos < ft_strlen(split_tokens))
    {
        pos_dolar = ft_encontrar_dolar(split_tokens, pos);//guarda la posicion del dolar
        if(pos_dolar < 0)
            return (split_tokens);
        palabra_dolar = ft_extract_word(split_tokens, pos_dolar, &pos);
        //pos actulizada al final de la palabra +1 si esk existe continuacion
        //llamo a la funcion que busca en el execve
        word_exchange = "sustituto";
        cadena_ya_reestructurada = ft_remodelar_cadena(split_tokens, palabra_dolar, word_exchange);
        pos++;
    }
    //aqui mando la palabra al execve
    
    //tres separar a cachos la cadena
    
}
char *ft_remodelar_cadena(char *split_tokens, char *palabra_dolar, char *word_exchange, int pos_dolar)
{
    char *cadena_a_trozos = NULL;
    char *palabra_a_cambiar = NULL;
    char *cadena_parte_final = NULL;
    int pos = 0;
    int num_chars = 0;

    cadena_a_trozos = ft_cpy_part(split_tokens, &pos, pos_dolar);
    palabra_a_cambiar = ft_cpy_part(split_tokens, &pos, ft_strlen(palabra_dolar));
    cadena_parte_final = ft_cpy_part(split_tokens, &pos, ft_strlen(split_tokens) - pos);
    cadena_a_trozos = ft_strjoin(cadena_a_trozos, word_exchange);
    cadena_a_trozos = ft_strjoin(cadena_a_trozos, cadena_parte_final);
    return (cadena_a_trozos);
}