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
        value = ft_calloc((end - start)+ 1);
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
//funciones para crear cmd

t_cmd *ft_create_new_cmd() {
    t_cmd *new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
    new_cmd->cmd = (char **)calloc(1, sizeof(char *));
    new_cmd->next = NULL;
    return new_cmd;
}

void ft_add_token_to_cmd(t_cmd *current_cmd, char *value, int *i)
{
	 size_t old_size;
	 size_t new_size;
    current_cmd->cmd[*i] = ft_strdup(value);
    (*i)++;
    // Reasignar memoria si es necesario
    if (*i % 10 == 0)
    {
        old_size = *i * sizeof(char *);
        new_size = (*i + 10) * sizeof(char *);
        current_cmd->cmd = ft_realloc(current_cmd->cmd, old_size, new_size);
    }
}
void ft_convert_tokens_to_cmds(t_general *g_data) 
{
	int i;

	i = 0;
    t_token *current_token;
    t_cmd *current_cmd;
    g_data->cmd;

	current_token = g_data->token;
	current_cmd = ft_create_new_cmd();
	cmd = current_cmd;
    while (current_token)
	{
        if (current_token->type_token == TOKEN_PIPE)
		{
            // Agregar NULL al final del comando actual
            current_cmd->cmd[i] = NULL;

            // Crear un nuevo t_cmd y agregarlo a la lista
            t_cmd *new_cmd = ft_create_new_cmd();
            current_cmd->next = new_cmd;

            // Pasar al siguiente comando y reiniciar el índice
            current_cmd = new_cmd;
            i = 0;
        }
		else
		{
            // Agregar el valor del token al comando actual
            ft_add_token_to_cmd(current_cmd, current_token->value, &i);
        }
        current_token = current_token->next;
    }
    // Agregar NULL al final del último comando
    current_cmd->cmd[i] = NULL;
}

t_cmd *ft_split_commands_by_pipe(char **tokens)
{
    int i = 0;
    t_cmd *head;
    t_cmd *current;
    t_temp temp;

	head = NULL;
	temp.data = ft_calloc(sizeof(char *), 1);
	temp.size = 0;
	temp.mem_size = sizeof(char *);
	current = head;
	head = ft_create_new_cmd();
    while (tokens[i])
	{
        if (ft_strcmp(tokens[i], "|") == 0)
        {
            current->cmd = temp.data;
            current->next = ft_create_new_cmd();
            current = current->next;
            temp.data = ft_calloc(sizeof(char *), 1);
            temp.size = 0;
            temp.mem_size = sizeof(char *);
        }
		else
            ft_add_token_to_cmd(current, tokens[i], &temp);
        i++;
    }
    current->cmd = temp.data;

    return head;
}
void ft_print_commands(t_cmd *cmd)
{
    t_cmd *current = cmd;
    int i = 0;

    while (current != NULL) {
        printf("Command %d:\n", i);
        char **temp = current->cmd;
        while (*temp) {
            printf("%s\n", *temp);
            temp++;
        }
        current = current->next;
        i++;
    }
}

void ft_generate_cmds_from_tokens(t_general *g_data)
{
    t_token *current_token;
    t_cmd *current_cmd;
    t_temp temp;

	current_cmd = NULL;
	temp.data = ft_calloc(sizeof(char *), 1);
	temp.size = 0;
	temp.mem_size = sizeof(char *);
    g_data->cmd = current_cmd;
	current_token = g_data->token;
    current_cmd = ft_create_new_cmd();
	while (current_token)
	{
        if (current_token->type_token == TOKEN_PIPE)
		{
            current_cmd->cmd = temp.data;
            current_cmd->next = ft_create_new_cmd();
            current_cmd = current_cmd->next;
            temp.data = ft_calloc(sizeof(char *), 1);
            temp.size = 0;
            temp.mem_size = sizeof(char *);
        }
		else
		{
            ft_add_token_to_cmd(current_cmd, current_token->value, &temp);
        }
        current_token = current_token->next;
    }
    current_cmd->cmd = temp.data;
}