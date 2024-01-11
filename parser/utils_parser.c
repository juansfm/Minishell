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
    char current_char;
    int count_quotes;

    count_quotes = 0;
    current_char = g_data->cpy_line[*pos];
    printf("\033[0;36m");
    printf("La comilla abierta(current) es: %c\n",current_char);
    printf("\033[0m");
    while(g_data->cpy_line[*pos] && ((count_quotes % 2 != 0) || (count_quotes == 0)))
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
    printf("\033[0;31m");
    printf("\nvalor de linea tras transfor[pos]: %s", g_data->cpy_line);
    printf("\033[0m");
    /*
    printf("\ncount fuera bucle: %d", count_quotes);
    printf("\033[0;31m");
    printf("\nLa cadena tras quote es: %s", g_data->cpy_line);
    printf("\033[0m");
    */
    if(!g_data->cpy_line[*pos] && (count_quotes % 2 != 0))
    {
        printf("Error: No se encontró el cierre de las comillas.\n");
        exit(EXIT_FAILURE);
    }
     if((count_quotes % 2 != 0))
    {
        printf("Error222: No se encontró el cierre de las comillas.\n");
        exit(EXIT_FAILURE);
    }
    *(pos) = *(pos) - 1; 
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
        printf("\033[0;36m");
        printf("\nRestaurado split_tokens[%d]: %s\n", i, split_tokens[i]);
        printf("\033[0m");
        i++;
    }
}

/*
int count_dolar(char *split_tokens)
{
    int i;
    int count;

    i = 0;
    count = 0;
    if (split_tokens[i] == '$' && quote_open == 0)
        count++;
    return count;
}
//expansion function, take $ and expand it
void ft_expand(t_general *g_data, int *pos)
{
    int i;

    i = 0;
}

*/