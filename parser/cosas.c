int	ft_process_quote_content_double(char *line, int len, int pos,
		t_token **head)
{
	char	quote;
	int		start;
	int		end;
	int		j;
	char	*value;

	quote = line[pos];
	start = pos + 1;
	end = start;
	j = 0;
	value = NULL;
	while (end < len && line[end] != quote)
		end++;
	if (end >= len)
	{
		printf("Error: No se encontró el cierre de las comillas.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		value = ft_calloc((end - start) + 1);
		while (j < (end - start))
		{
			value[j] = line[start + j];
			j++;
		}
		value[end] = '\0';
		ft_add_token_in_general(head, TOKEN_WORD, value);
		free(value);
	}
	return (pos);
}

int	ft_process_quote_content_sim(char *line, int len, int pos, t_token **head)
{
	int		end;
	int		j;
	char	*value;

	int start = pos + 1; //despues de quitar la comilla
	end = start;
	j = 0;
	char quote = line[pos]; //compruebo que es igual a la comilla llamada
	value = NULL;
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
	return (pos); // Actualizar la posición
}

int	ft_process_word(char *line, int len, int pos, t_token **head)
{
	int		start;
	int		end;
	int		j;
	char	*value;

	start = pos;
	end = start;
	j = 0;
	value = NULL;
	while (end < len && !ft_char_reserved(line[end]))
		end++;
	value = malloc(sizeof(char) * ((end - start) + 1));
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

char	*funcion_que_lo_lleva_todo(t_general *g_data, char *split_tokens)
	//esta funcion la llamare mas veces por si hay mas dolar
{
	int pos = 0;
	int pos_dolar = 0;
	char *palabra_dolar = NULL;
	char *word_exchange = NULL;
	char *cadena_ya_reestructurada = NULL;
	g_data = NULL;

	while (pos < ft_strlen(split_tokens))
	{
		pos_dolar = ft_encontrar_dolar(split_tokens, pos);
			//guarda la posicion del dolar
		if (pos_dolar < 0)
			return (split_tokens);
		palabra_dolar = ft_extract_word(split_tokens, pos_dolar, &pos);
		//pos actulizada al final de la palabra +1 si esk existe continuacion
		//llamo a la funcion que busca en el execve
		word_exchange = "sustituto";
		cadena_ya_reestructurada = ft_remodelar_cadena(split_tokens,
				palabra_dolar, word_exchange);
		pos++;
	}
	//aqui mando la palabra al execve

	//tres separar a cachos la cadena
}
char	*ft_remodelar_cadena(char *split_tokens, char *palabra_dolar,
		char *word_exchange, int pos_dolar)
{
	char	*cadena_a_trozos;
	char	*palabra_a_cambiar;
	char	*cadena_parte_final;
	int		pos;
	int		num_chars;

	cadena_a_trozos = NULL;
	palabra_a_cambiar = NULL;
	cadena_parte_final = NULL;
	pos = 0;
	num_chars = 0;
	cadena_a_trozos = ft_cpy_part(split_tokens, &pos, pos_dolar);
	palabra_a_cambiar = ft_cpy_part(split_tokens, &pos,
			ft_strlen(palabra_dolar));
	cadena_parte_final = ft_cpy_part(split_tokens, &pos, ft_strlen(split_tokens)
			- pos);
	cadena_a_trozos = ft_strjoin(cadena_a_trozos, word_exchange);
	cadena_a_trozos = ft_strjoin(cadena_a_trozos, cadena_parte_final);
	return (cadena_a_trozos);
}
//funciones para crear cmd

t_cmd	*ft_create_new_cmd()
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	new_cmd->cmd = (char **)calloc(1, sizeof(char *));
	new_cmd->next = NULL;
	return (new_cmd);
}

void	ft_add_token_to_cmd(t_cmd *current_cmd, char *value, int *i)
{
	size_t	old_size;
	size_t	new_size;

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
void	ft_convert_tokens_to_cmds(t_general *g_data)
{
	int		i;
	t_token	*current_token;
	t_cmd	*current_cmd;
	t_cmd	*new_cmd;

	i = 0;
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
			new_cmd = ft_create_new_cmd();
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

t_cmd	*ft_split_commands_by_pipe(char **tokens)
{
	int		i;
	t_cmd	*head;
	t_cmd	*current;
	t_temp	temp;

	i = 0;
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
	return (head);
}
void	ft_print_commands(t_cmd *cmd)
{
	t_cmd	*current;
	int		i;
	char	**temp;

	current = cmd;
	i = 0;
	while (current != NULL)
	{
		printf("Command %d:\n", i);
		temp = current->cmd;
		while (*temp)
		{
			printf("%s\n", *temp);
			temp++;
		}
		current = current->next;
		i++;
	}
}

void	ft_generate_cmds_from_tokens(t_general *g_data)
{
	t_token	*current_token;
	t_cmd	*current_cmd;
	t_temp	temp;

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
char	*ft_extract_word(char *str, int pos_dolar, int *pos)
	//pos es donde esta el dolar
{
	int start;
	int end;
	char *word;
	int fin;

	word = NULL;
	fin = 0;
	start = pos_dolar;
	end = start + 1;
	if (str[end] && ft_isdigit(str[end]))
	{
		// word = //lamar al execve con el dolar y el numero solamente
		fin = 1;
	}
	while (str[end] && (fin == 0))
	{
		if (!ft_isalnum(str[end]))
		{
			end--;
			break ;
		}
		end++;
	}
	word = ft_substr(str, start + 1, end - start);
	*pos = end;
	return (word); //esta palabra es la que va a ir al execve sin dolar
}

/*copia de que lo lleva todo sin modificar
char	*funcion_que_lo_lleva_todo(t_general *g_data,
		char *split_tokens)//esta funcion la llamare mas veces por si hay mas dolar
{
	int pos = 0;
	int pos_dolar = 0;
	char *palabra_dolar = NULL;
	char *word_exchange = NULL;
	char *cadena_ya_reestructurada = NULL;
	g_data = NULL;

	pos_dolar = ft_encontrar_dolar(split_tokens,
		pos);//guarda la posicion del dolar
	if(pos_dolar < 0)
		return (split_tokens);
	palabra_dolar = ft_extract_word(split_tokens, pos_dolar, &pos);
	//pos actulizada al final de la palabra +1 si esk existe continuacion
	//word = funcion que llama al execve(palabra_dolar))
	//llamo a la funcion que busca en el execve
	word_exchange = "sustituto";
	cadena_ya_reestructurada = ft_remodelar_cadena(split_tokens, palabra_dolar,
		word_exchange, pos_dolar);
	printf("\033[0;35m");
	printf("\nla cadena ya reestructurada: %s\n", cadena_ya_reestructurada);
	printf("\033[0m");
	//aqui mando la palabra al execve
	//word = funcion que llama al execve(palabra_dolar))
	//tres separar a cachos la cadena
	return (cadena_ya_reestructurada);
}
*/
//de esta funcion hay que modificar que cuando haya algo detras de la funcion dolar
/*char *funcion_que_lo_lleva_todo(t_general *g_data, char *split_tokens)
{
	char	*cadena_a_trozos;
	char	*palabra_dolar;
	char	*palabra_a_cambiar;
	int		pos;
	int		pos_dolar;
	int		num_chars;

	cadena_a_trozos = NULL;
	palabra_dolar = NULL;
	palabra_a_cambiar = NULL;
	//char *cadena_parte_final = NULL;
	pos = 0;
	pos_dolar = 0;
	num_chars = 0;
	g_data = NULL;
	printf("\033[0;35m");
	printf("\nvalor split token en funcion dentro de que lo lleva todo: %s\n",
		split_tokens);
	printf("\033[0m");
	pos_dolar = ft_encontrar_dolar(split_tokens, pos);
	printf("\nesta es la pos dolar tras salir(%i)\n", pos_dolar);
	if(pos_dolar < 0)
		return (split_tokens);
	palabra_dolar = ft_extract_word(split_tokens, pos_dolar);
   
	//aqui llamamos al execve con la palabra que nos devuelve la funcion extract_word
	printf("\033[0;31m");
	printf("\nesta es la palabra que tiene el dolar: %s\n", palabra_dolar);
	printf("\033[0m");
//hasta aqui hace solo un dolar por cadena,
	si hay varios dolar en una cadena no lo hace
	if(palabra_dolar != NULL)
	{
		//funcion que mira si existe la variable de entorno
		//si existe la variable de entorno, se sustituye por su valor
		printf("\nHEMOS ENCONTRADO DOLAR VALIDO\n");
		palabra_a_cambiar = "Sustituto";//esto se sustituye por el resultado de la funcionque mira si existe la variable de entorno
		if (palabra_a_cambiar != NULL)//si existe la variable de entorno
			num_chars = pos_dolar - pos;
			cadena_a_trozos = ft_cpy_part(split_tokens, &pos, num_chars);     
	//esto quiero que sea antes del dolar
			printf("\nla cadena a trozos: %s\n", cadena_a_trozos);
			printf("\npos tras copiar principio: %d\n", pos);
			num_chars = ft_strlen(palabra_a_cambiar);
			cadena_a_trozos = ft_strjoin(cadena_a_trozos, palabra_a_cambiar);
			printf("\033[0;35m");
			printf("\nunion principio con palabra modificada:
		%s\n",cadena_a_trozos);
			printf("\033[0m");
		   
	//aqui tengo que unir la parte siguiente de la cadena que esta detras del dolar,previamente tendria que guardar esa info en algun lado
			//cadena_parte_final = ft_cpy_part(split_tokens, &pos,
		num_chars);      //esto quiero que sea despues del dolar
			//printf("\nla cadena a trozos otro cacho final: %s\n",
		cadena_parte_final);
			//cadena_a_trozos = ft_strjoin(cadena_a_trozos, cadena_parte_final);
			printf("\nla cadena a trozos juntitos final: %s\n",
		cadena_a_trozos);
		//else
		   
	//la variable se sustituye por nada(dolar lo que sea desaparece)y se sigue con la cadena
	   
	//lo que salga de aqui sera la cadena modificada en caso de $ valido o no
	}
	return (cadena_a_trozos);
}*/
//yo llamo a la funcion que lo lleva todo tras hacer limpia de comilla y tenerlo a cachitos,
	es decir
//le entrarian varias cadenas por tanto hay que hacer un bucle que llame varias veces a la funcion
//quiero
//despues de esta funcion tengo la funcion que me devuelve el significado de la palabra que tenia dolar
//tras esa funcion tengo que pegar la palabra a la cadena que me dejo la funcion cpy_part,
	tras juntarlo tengo que
// pegarle lo que venga despues de la palabra sacsada de $lo que sea
//[listo]1
	- la funcion busca carcacter hay que añadirle que si esta entre comillas simples no lo haga,
	pero para eso hay que ver si hay algunas comillas aabiertas antes de la
//[listo]2 - si encuentra el caracter llama a la funcion extrae_word[listo]
//3
	- la funcion extrae_word llamara a la funcion que mira variables de entorno[aun no]
//4
	- da igual lo que salga ese valor ha de ser sustituido por la palabra extraida de la funcion extrae_word[aun no]
//[listo]5 - se llama a la funcion que copia todo hasta antes del dolar,
	se reserva[listo?]
//[listo]6
	- se crea una nueva cadena con el tamaño de la union de la cadena reservada y la palabra extraida
//[listo]7
	- se crea una nueva cadena con el tamaño de la union y lo que haya detras de la cadena extraida
//[mirarlo]obviamente hay que ir limpiando las cadenas que se han ido fusionando,
	esto es un paso que va por que va dentro de todo el proceso
//8 - si se vuelve a pasar la funcion busca_caracter y no encuentra nada,
	se copia lo que quede de la cadena original
//Partes de funcion expandir
//1-miro si hay dolar
//2-si lo hay,
	pregunto si puedo expandir,es decir que no este entre comillas simples
//3-si es un no, dejo la cadena como esta,
	y si no he terminado la cadena vuelvo a mirar si hay dolar
//4-si es un si, miro si lo que devuelve es un null o otra cosa
//5-si es un null tengo que rediseñar una n
//DE DENTRO DE PARSE_TOKENS()
/*
	ft_restore_quotes(g_data->split_tokens);
	//aqui llamo a la funcion que me expande las variables,
	ya que aun lo tengo en
	// cadenas mas pequeñas
	i = 0;
	pos = 0;
	while(g_data->split_tokens[i])
	{
		while(ft_encontrar_dolar(*g_data->split_tokens, pos) > 0)
			g_data->split_tokens[i] = funcion_que_lo_lleva_todo(g_data,
		g_data->split_tokens[i]);
		printf("\nPost funcion que lo lleva todo: %s\n",
		g_data->split_tokens[i]);
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
//cosas de tokens
void	ft_print_tokens(t_token *head)
{
	while (head != NULL)
	{
		printf("Token Type: %d, Value: %s\n", head->type_token, head->value);
		head = head->next;
	}
}

int	ft_get_token_type(char *value)
{
	if (ft_strcmp(value, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strcmp(value, "<") == 0)
		return (TOKEN__IN);
	else if (ft_strcmp(value, ">") == 0)
		return (TOKEN__OUT);
	else if (ft_strcmp(value, "<<") == 0)
		return (TOKEN_HERE_DOC_IN);
	else if (ft_strcmp(value, ">>") == 0)
		return (TOKEN_HERE_DOC_OUT);
	else if (ft_strchr(value, '=') != NULL)
		return (TOKEN__ARG);
	else
		return (TOKEN_CMD);
}

t_token	*ft_new_token(char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->len = ft_strlen(value);
	token->type_token = ft_get_token_type(value);
	token->next = NULL;
	return (token);
}

t_token	*ft_convert_to_tokens(char **str)
{
	t_token	*head;
	t_token	*current;
	char	*token;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (str[i] != NULL)
	{
		token = str[i];
		if (head == NULL)
		{
			head = ft_new_token(token);
			current = head;
		}
		else
		{
			current->next = ft_new_token(token);
			current = current->next;
		}
		i++;
	}
	return (head);
}
/*
t_token	*ft_new_token(int type_token, char *value)
{
	int len;
	t_token *new_node;

	len = ft_strlen(value);
	new_node = ft_calloc(1, sizeof(t_token));
	if (new_node == NULL)
	{
		printf("Error: No se pudo asignar memoria para el nuevo nodo.\n");
		return (NULL);
	}
	new_node->len = len;
	new_node->type_token = type_token;
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

// Función que añade un nuevo token a la lista dentro de t_general
void	ft_add_token_in_general(t_token **head, int type_token, char *value)
{
	t_token *new_node;
	t_token	*current;

	new_node = NULL;
	new_node = ft_new_token(type_token, value);
	if (new_node == NULL)
	{
		printf("Error: No se pudo crear el nuevo token.\n");
		return ;
	}
	if (*head == NULL)
	{
		*head = new_node; // Si es el primer nodo,
	asigna el nuevo nodo como cabeza de la lista
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next; // Avanza al último nodo
		}
		current->next = new_node; // Agrega el nuevo nodo al final de la lista
	}
}

void	ft_free_tokens(t_token *head) 
{
	while (head != NULL) 
	{
		t_token *temp = head;
		head = head->next;
		free(temp->value);  // Liberamos la memoria del valor
		free(temp);
	}
}
*/

/*
t_cmd	*ft_cmd_new(char *arg)
{
	t_cmd	*cmd;
	char	**mtx;
	int		i;
	int		j;
	int		len;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->infile = -1;
	cmd->outfile = -1;
	mtx = ft_split(arg, ' ');
	i = -1;
	len = 0;
	while (mtx[++i] != NULL)
	{
		if (!ft_strcmp(mtx[i], "<") && mtx[i + 1] != NULL)
		{
			i++;
			cmd->infile_name = ft_strdup(mtx[i]);
			if (cmd->infile != -1)
				close(cmd->infile);
			cmd->infile = open(cmd->infile_name, O_RDONLY);
		}
		else if (!ft_strcmp(mtx[i], ">") && mtx[i + 1] != NULL)
		{
			i++;
			cmd->outfile_name = ft_strdup(mtx[i]);
			if (cmd->outfile != -1)
				close(cmd->outfile);
			cmd->outfile = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		}
		else if (!ft_strcmp(mtx[i], ">>") && mtx[i + 1] != NULL)
		{
			i++;
			cmd->outfile_name = ft_strdup(mtx[i]);
			cmd->outfile = open(cmd->outfile_name,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
			len++;
	}
	cmd->cmd = ft_calloc(len + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (mtx[++i] != NULL)
	{
		if ((!ft_strcmp(mtx[i], "<") || !ft_strcmp(mtx[i], ">")
				|| !ft_strcmp(mtx[i], ">>")) && mtx[i + 1] != NULL)
			i++;
		else
		{
			cmd->cmd[j] = ft_strdup(mtx[i]);
			j++;
		}
	}
	// cmd->cmd = ft_split(arg, ' ');
	cmd->next = NULL;
	return (cmd);
}
*/

/* nuevo creo que desecho
void	ft_cmd_lst(t_general *g_data)
{
	t_cmd *cmd;
	t_token	*current_token;
	int		i;

	current_token = g_data->token;
	i = 0;
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

/*
void	ft_process_args(t_cmd *cmd, char **mtx)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (mtx[++i] != NULL)
	{
		if (!ft_strcmp(mtx[i], "<") && mtx[i + 1] != NULL)
		{
			i++;
			cmd->infile_name = ft_strdup(mtx[i]);
			if (cmd->infile != -1)
				close(cmd->infile);
			cmd->infile = open(cmd->infile_name, O_RDONLY);
		}
		else if (!ft_strcmp(mtx[i], ">") && mtx[i + 1] != NULL)
		{
			i++;
			cmd->outfile_name = ft_strdup(mtx[i]);
			if (cmd->outfile != -1)
				close(cmd->outfile);
			cmd->outfile = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_TRUNC,
		0644);
		}
		else if (!ft_strcmp(mtx[i], ">>") && mtx[i + 1] != NULL)
		{
			i++;
			cmd->outfile_name = ft_strdup(mtx[i]);
			cmd->outfile = open(cmd->outfile_name,
		O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
			len++;
	}
	cmd->cmd = ft_calloc(len + 1, sizeof(char *));
}
*/

/*quitar comillas no esta implementado
void	ft_quitar_comillas(char* cadena)
{
	int	i;
	int	j;
	int	dentroComillas;

	i = 0;
	j = 0;
	dentroComillas = 0;
	if (cadena == NULL)
	{
		printf("Error: Cadena nula.\n");
		return ;
	}
	while (cadena[i] != '\0')
	{
		if (cadena[i] == '\"' || cadena[i] == '\'')
		{
			dentroComillas = !dentroComillas;
	// Cambiar el estado si encontramos una comilla
		}
		if (!dentroComillas && (cadena[i] == '\"' || cadena[i] == '\''))
		{
			i++; // Saltar la comilla exterior
		}
		else
		{
			cadena[j] = cadena[i];
			j++;
			i++;
		}
	}
	cadena[j] = '\0';
}

void	ft_reordenar_palabras(char *cadena)//no se usa
{
	int idx;
	int inicio;
	int len;

	idx = 0;
	inicio = 0;
	while (cadena[idx] != '\0')
	{
		if (cadena[idx] == ' ')
		{
			len = idx - inicio;
			if (cadena[idx + 1] == '\0')
			{
				len++;
			}
			if (inicio != idx)
			{
				ft_memmove(cadena + inicio, cadena + idx + 1, len);
				if (cadena[idx + 1] == '\0')
				{
					idx--;
				}
				else
				{
					idx -= 2;
				}
			}
			inicio = idx + 1;
		}
		idx++;
	}
}
*/
/*funcion que divido en 2
char	**ft_eliminar_espacios(char **cadena_de_cadenas)
{
	int i;
	int cantidad_cadenas;
	char **resultado;
	int j;

	cantidad_cadenas = 0;
	i = 0;
	resultado = NULL;
	// Contar la cantidad de cadenas válidas
	while (cadena_de_cadenas[i] != NULL)
	{
		if (ft_strcmp(cadena_de_cadenas[i], " ") != 0)
			cantidad_cadenas++;
		i++;
	}
	resultado = ft_calloc((cantidad_cadenas + 1), sizeof(char *));
	// Reservar memoria para el resultado
	if (!resultado)
		return (NULL); // Manejar error de asignación de memoria
	// Eliminar cadenas que contienen solo espacios
	i = 0;
	j = 0;
	while (cadena_de_cadenas[i] != NULL)
	{
		if (ft_strcmp(cadena_de_cadenas[i], " ") != 0)
		{
			resultado[j] = cadena_de_cadenas[i];
			j++;
		}
		i++;
	}
	resultado[cantidad_cadenas] = NULL; // Establecer el nuevo final del arreglo
	return resultado;
}
*/

void	ft_quita_comillas(t_general *g_data)
{
	int		i;
	int		j;
	int		k;
	int		len;
	int		in_quotes;
	char	quote_char;
	char	*temp;
	char	*temp2;

	i = 0;
	j = 0;
	k = 0;
	len = 0;
	in_quotes = 0;
	quote_char = '\0';
	temp = NULL;
	temp2 = NULL;
	while (g_data->split_tokens[i])
	{
		len = ft_strlen(g_data->split_tokens[i]);
		temp = ft_calloc(len + 1, sizeof(char));
		temp2 = ft_calloc(len + 1, sizeof(char));
		while (g_data->split_tokens[i][j])
		{
			if (g_data->split_tokens[i][j] == '\"'
				|| g_data->split_tokens[i][j] == '\'')
			{
				if (in_quotes)
				{
					if (g_data->split_tokens[i][j] == quote_char)
					{
						// Closing quote matches opening quote
						in_quotes = 0;
						quote_char = '\0';
					}
					else
					{
						// Quote doesn't match opening quote, so copy it
						temp[k] = g_data->split_tokens[i][j];
						k++;
					}
				}
				else
				{
					// Not in quotes, so start a new quote sequence
					in_quotes = 1;
					quote_char = g_data->split_tokens[i][j];
				}
				j++;
			}
			else
			{
				temp[k] = g_data->split_tokens[i][j];
				k++;
				j++;
			}
		}
		temp[k] = '\0';
		temp2 = ft_strdup(temp);
		free(g_data->split_tokens[i]);
		g_data->split_tokens[i] = ft_strdup(temp2);
		free(temp);
		free(temp2);
		i++;
		j = 0;
		k = 0;
	}
}

/*
	int i;
	int j;
	int k;
	int len;
	char *temp;
	char *temp2;

	i = 0;
	j = 0;
	k = 0;
	len = 0;
	temp = NULL;
	temp2 = NULL;
	while(g_data->split_tokens[i])
	{
		len = ft_strlen(g_data->split_tokens[i]);
		temp = ft_calloc(len + 1, sizeof(char));
		temp2 = ft_calloc(len + 1, sizeof(char));
		while(g_data->split_tokens[i][j])
		{
			if(g_data->split_tokens[i][j] == '\"'
		|| g_data->split_tokens[i][j] == '\'')
				j++;
			else
			{
				temp[k] = g_data->split_tokens[i][j];
				k++;
				j++;
			}
		}
		temp[k] = '\0';
		temp2 = ft_strdup(temp);
		free(g_data->split_tokens[i]);
		g_data->split_tokens[i] = ft_strdup(temp2);
		free(temp);
		free(temp2);
		i++;
		j = 0;
		k = 0;
	}
*/