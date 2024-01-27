#include "minishell.h"

void ft_entrecomillas(char char_cmd, t_general *g_data)
{
	int	i;
	
	i = 0;
	if (char_cmd == '\"' && g_data->quote_double == 0 && g_data->quote_simple == 0)
		g_data->quote_double = 1;
	else if (char_cmd == '\'' && g_data->quote_double == 0 && g_data->quote_simple == 0)
			g_data->quote_simple = 1;
	else if(char_cmd == '\"' && g_data->quote_double == 1)
		g_data->quote_double = 0;
	else if(char_cmd == '\'' && g_data->quote_simple == 1)
			g_data->quote_simple = 0;
}

int ft_existe_dolar_valido(char *comand)
{
	int	i;
	int	quote_simple;
	int	quote_double;

	i = 0;
	quote_simple = 0;
	quote_double = 0;
	while (comand[i])
	{
		if (comand[i] == '\"')
			quote_double = (quote_double + 1) % 2;
		else if (comand[i] == '\'')
		{
			if (quote_double == 0)
				quote_simple = (quote_simple + 1) % 2;
		}
		else if (comand[i] == '$' && quote_simple == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_vamos_a_expandir(t_general *g_data)
{
	int	i;
	int	pos;
	int	j;

	i = 0;
	pos = 0;
	j = 0;
	while (g_data->cmd->cmd[i])
	{
		if ((ft_existe_dolar_valido(g_data->cmd->cmd[i]) > -1))
			g_data->cmd->cmd[i] = ft_expand_all(g_data, g_data->cmd->cmd[i]);
		i++;
	}
}

char	*ft_get_word_exchange(t_general *g_data, char *palabra_dolar)
{
	t_env	*env;
	char	*word_exchange;

	if (ft_env_search(g_data, palabra_dolar))
	{
			env = ft_env_search(g_data, palabra_dolar);
			word_exchange = ft_strdup(env->valor);
	}
	else
		word_exchange = ft_strdup("");
	return (word_exchange);
}


int ft_comprobar_dolar(char cmd_char, t_general *g_data)//me da menos 1 cuando el dolar no es valido
{

	if (cmd_char == '$' && g_data->quote_simple == 0)
		return (0);
	return (-1);
}
/*
char	*ft_process_dolar(t_general *g_data, char *string_restruc, int pos_dolar)
{
	char	*palabra_dolar;
	char	*word_exchange;

	palabra_dolar = ft_extract_word(string_restruc, pos_dolar);
	if (palabra_dolar[0] == '\0')
	{
		return (string_restruc);
	}
	word_exchange = ft_get_word_exchange(g_data, palabra_dolar);
	string_restruc = ft_remodelar_cadena(string_restruc, palabra_dolar,
			word_exchange, pos_dolar);
	free(palabra_dolar);
	free(word_exchange);
	return (string_restruc);
}
*/
//ejemplo $USER// aaa$USER//$USER$USER//aaa$USER$USER//aaa$USER$pepe$USER//$//$pepe$//"  $USER $" // " $ $USER $PEPE $? "
char	*ft_expand_all(t_general *g_data, char *cmd)
{
	int		pos_dolar;
	char	*string_restruc;//la voy a unar para ir uniendola poco a poco
	int i;
	char *word_exchange; //lo que obtenemos de la funcion get_word_exchange
	char *palabra_extraida;// la palabra que sale de la funcion extract_word

	i = 0;
	pos_dolar = -1;
	string_restruc = ft_strdup("");
	word_exchange = NULL;
	while (cmd[i])
	{
		ft_entrecomillas(cmd[i], g_data);
		if(ft_comprobar_dolar(cmd[i], g_data) == 0)
			pos_dolar = i;
		printf("\npos_dolar: %d\n", pos_dolar);
		if(pos_dolar == -1)
		{
			string_restruc = ft_charjoin_free(string_restruc, cmd[i]);
			printf("\nstring_restruc: %s\n", string_restruc);
			i++;
		}
		else
		{
			palabra_extraida = ft_extract_word(cmd, pos_dolar);
			i++;
			printf("\npalabra_extraida: %s\n", palabra_extraida);
			if (ft_strcmp(palabra_extraida, "?") == 0)
			{
				printf("\nstatus: %d\n", g_data->status);
				string_restruc = ft_strjoin_free(string_restruc, ft_itoa(g_data->status));
				i++;
			}
			else if (!(*palabra_extraida) || (ft_char_reserved(palabra_extraida[0]) == 1))
			{
				printf("\nHEMOS ENTRADO cuando no exite palabra_ext o hay un separador %s\n", string_restruc);
				string_restruc = ft_charjoin_free(string_restruc, '$');
				i++;
			}
			else
			{
				word_exchange = ft_get_word_exchange(g_data, palabra_extraida);
				string_restruc = ft_strjoin_free(string_restruc, word_exchange);
				i += ft_strlen(palabra_extraida);
			}
			free(palabra_extraida);
			// free(word_exchange);
		}
		pos_dolar = -1;
		
	}
	g_data->quote_double = 0;
	g_data->quote_simple = 0;
	return (string_restruc);
}

//funcion que comprueba si existe la variable de entorno que le paso

//falta comprobar esta funcion extract_word

//esta funcion es para sacar la palabra que le mandare al execve,
//este me mirara, recibo la pos de donde esta el dollar
char	*ft_extract_word(char *str, int pos_dolar)
{
	int		start;
	int		end;
	char	*word;
	int		fin;

	word = NULL;
	fin = 0;
	start = pos_dolar;
	end = start + 1;
	if (str[end] && ft_isdigit(str[end]))
		fin = 1;
	if(str[pos_dolar + 1] == '?')
		fin = 1;
	while (str[end] && (fin == 0))
	{

		if (!ft_isalnum(str[end]))//aqui quiero que se pare en el primer caracter que no sea alfanumerico
		{
			end--;
			break;
		}
		end++;
	}
	word = ft_substr(str, start + 1, end - start);
	return (word);
}

//la funcion devuelve la posicion donde esta el primer dolar o menos 1 si no lo encuentra(dolar valido)
//ahora esta modificada para que se le pase la posicion desde donde comienza a buscar

//si la funcion busca_caracter encuentra el caracter que le paso,
// devuelve la posicion donde esta el dolar
	//esta funcion es solo una parte de otra funcion,
	// esto me guarda en una cadena todo hasta donde esta el dolar

	//queremos que esta funcion nos sirva para coger desde ubicaciones dadas

char	*ft_cpy_part(char *str, int *pos, int num_chars)
{
	int		start;
	char	*dest;

	start = *pos;
	if (num_chars > 0)
		dest = ft_substr(str, start, num_chars);
	else
		dest = ft_strdup("");
	*pos = start + num_chars;
	return (dest);
}
/*
char	*ft_remodelar_cadena(char *split_tokens, char *palabra_dolar, char *word_exchange, int pos_dolar)
{
	char	*cadena_a_trozos;
	char	*palabra_a_cambiar;
	char	*cadena_parte_final;
	int		pos;

	cadena_a_trozos = NULL;
	palabra_a_cambiar = NULL;
	cadena_parte_final = NULL;
	pos = 0;
	cadena_a_trozos = ft_cpy_part(split_tokens, &pos, pos_dolar);
	palabra_a_cambiar = ft_cpy_part(split_tokens, &pos, ft_strlen(palabra_dolar)
			+ 1);
	cadena_parte_final = ft_cpy_part(split_tokens, &pos, ft_strlen(split_tokens)
			- pos);
	if (cadena_a_trozos != NULL)
		cadena_a_trozos = ft_strjoin_free(cadena_a_trozos, word_exchange);
	else
		cadena_a_trozos = ft_strdup(word_exchange);
	cadena_a_trozos = ft_strjoin_free(cadena_a_trozos, cadena_parte_final);
	free(cadena_parte_final);
	free(palabra_a_cambiar);
	return (cadena_a_trozos);
}
*/