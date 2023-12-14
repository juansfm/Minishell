#include "minishell.h"

int ft_char_reserved(char c)
{
    if(c == ' ' || c == '|' || c == '>' || c == '<')
        return 1;
    return 0;
}

void ft_print_tokens(t_token *head) 
{
    while (head != NULL) 
    {
        printf("Token Type: %d, Value: %s\n", head->type_token, head->value);
        head = head->next;
    }
}

int ft_isspace(int c) 
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}


/**
 * Replaces spaces within quotes with a non-printable control character like '\1'.
 * 
 * @param line The string to process.
 * @param len The length of the string.
 * @param pos The current position in the string.
 */
void ft_process_quote(t_general *g_data, int *pos)
{
    /*sustituir los espacios por una variable de control no imprimible como el \1 cuando recorra la cadena y me encuentre entre comillas*/
    char current_char;
    int count_quotes;

    count_quotes = 1;
    current_char = g_data->cpy_line[*pos];
    (*pos)++;
    while(g_data->cpy_line[*pos] && (count_quotes % 2 != 0))
    {
        if(g_data->cpy_line[*pos] == ' ')
            g_data->cpy_line[*pos] = '\1';
        else if(g_data->cpy_line[*pos] == '|')
            g_data->cpy_line[*pos] = '\2';
        else if(g_data->cpy_line[*pos] == '>')
            g_data->cpy_line[*pos] = '\3';
        else if(g_data->cpy_line[*pos] == '<')
            g_data->cpy_line[*pos] = '\4';
        else if(g_data->cpy_line[*pos] == current_char)
            count_quotes++; 
        (*pos)++;
    }
    if(!g_data->cpy_line[*pos] && (count_quotes % 2 != 0))
    {
        printf("Error: No se encontró el cierre de las comillas.\n");
        exit(EXIT_FAILURE);
    }
}
void ft_process_pipe_in_quote(t_general *g_data, int *pos)
{
    char current_char;
    int count_quotes;

    count_quotes = 1;
    current_char = g_data->cpy_line[*pos];
    (*pos)++;
    while(g_data->cpy_line[*pos] && (count_quotes % 2 != 0))
    {
        if(g_data->cpy_line[*pos] == '|')
            g_data->cpy_line[*pos] = '\2';
        if(g_data->cpy_line[*pos] == current_char)
            count_quotes++; 
        (*pos)++;
    }
    if(!g_data->cpy_line[*pos] && (count_quotes % 2 != 0))
    {
        printf("Error: No se encontró el cierre de las comillas.\n");
        exit(EXIT_FAILURE);
    }
}

void ft_process_red_in_quote(t_general *g_data, int *pos)
{
    /*sustituir los espacios por una variable de control no imprimible como el \1 cuando recorra la cadena y me encuentre entre comillas*/
    char current_char;
    int count_quotes;

    count_quotes = 1;
    current_char = g_data->cpy_line[*pos];
    (*pos)++;
    while(g_data->cpy_line[*pos] && (count_quotes % 2 != 0))
    {
        if(g_data->cpy_line[*pos] == '>')
            g_data->cpy_line[*pos] = '\3';
        if(g_data->cpy_line[*pos] == '<')
            g_data->cpy_line[*pos] = '\4';
        if(g_data->cpy_line[*pos] == current_char)
            count_quotes++; 
        (*pos)++;
    }
    if(!g_data->cpy_line[*pos] && (count_quotes % 2 != 0))
    {
        printf("Error: No se encontró el cierre de las comillas.\n");
        exit(EXIT_FAILURE);
    }
}

//funcion que va recorriendo un doble puntero de cadenas
//y comprueba si hay \1 en las cadenas y si es asi, las sustituye por espacios
void ft_restore_quotes(char **split_tokens)
{
    int i;
    int j;

    i = 0;
    while(split_tokens[i])
    {
        j = 0;
        while(split_tokens[i][j])
        {
            if(split_tokens[i][j] == '\1')
                split_tokens[i][j] = ' ';
            else if(split_tokens[i][j] == '\2')
                split_tokens[i][j] = '|';
            else if(split_tokens[i][j] == '\3')
                split_tokens[i][j] = '>';
            else if(split_tokens[i][j] == '\4')
                split_tokens[i][j] = '<';
            j++;
        }
        printf("Restaurado split_tokens[%d]: %s\n", i, split_tokens[i]);
        i++;
    }
}

//funcion que recorre un doble puntero y comprueba si hay comillas
//y si es asi, levanta una flag y mira si hay comillas en la siguiente cadena
//y si entre las comillas hay una variable $, si es asi llama la funcion expandir


/*
char *ft_process_word(char *line, int len, int *pos)
{
    //si veo un caracter especial o separador, me quedo con la cadena hasta esa posicion y devuelvo la cadena
    char *s;
    char *aux;
    int start;
    // n n "a's$As2">wda  w"aaa 
    start = *pos;
    while(line[*pos] && !ft_char_reserved(line[*pos]))
    {
        if(line[*pos] == '\"' || line[*pos] == '\'')
        {
            s = ft_substr(line, start, *pos - start);
            aux = ft_process_quote(line, len, pos);
            s = ft_strjoin(s, aux);
        }
        (*pos)++;
    }
    //s = ft_substr(line, start, *pos - start);
    return s;
}
*/

/*
void ft_modify_string(char *str)
{
    int len = ft_strlen(str);
    int i = 0;

    while (i < len)
    {
        if (str[i] == '|' || str[i] == '<' || str[i] == '>')
        {
            if (i > 0 && !ft_isspace(str[i - 1]))
            {
                ft_memmove(&str[i + 1], &str[i], len - i);
                str[i] = ' ';
                len++;
                i++;
            }

            if (i < len - 1 && !ft_isspace(str[i + 1]))
            {
                ft_memmove(&str[i + 2], &str[i + 1], len - (i + 1));
                str[i + 1] = ' ';
                len++;
                i++;
            }
        }
        else if (str[i] == '>' && i < len - 1 && str[i + 1] == '>')
        {
            if (i > 0 && !ft_isspace(str[i - 1]))
            {
                ft_memmove(&str[i + 2], &str[i], len - i);
                str[i] = ' ';
                str[i + 1] = ' ';
                len += 2;
                i += 2;
            }

            if (i < len - 2 && !ft_isspace(str[i + 2]))
            {
                ft_memmove(&str[i + 3], &str[i + 2], len - (i + 2));
                str[i + 2] = ' ';
                len++;
                i += 2;
            }
        }
        else if (str[i] == '<' && i < len - 1 && str[i + 1] == '<')
        {
            if (i > 0 && !ft_isspace(str[i - 1]))
            {
                ft_memmove(&str[i + 2], &str[i], len - i);
                str[i] = ' ';
                str[i + 1] = ' ';
                len += 2;
                i += 2;
            }

            if (i < len - 2 && !ft_isspace(str[i + 2]))
            {
                ft_memmove(&str[i + 3], &str[i + 2], len - (i + 2));
                str[i + 2] = ' ';
                len++;
                i += 2;
            }
        }
        i++;
    }
}
*/