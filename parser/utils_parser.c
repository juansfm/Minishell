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
void ft_restore_spaces(char **split_tokens)
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
            j++;
        }
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