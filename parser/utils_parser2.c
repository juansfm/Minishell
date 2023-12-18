#include "minishell.h"

char *ft_extract_token(char *cpy_line, int start, int end)
{
    int token_length;
    char *token; 
    int i;

    token_length = end - start;
    token = malloc(sizeof(char) * (token_length + 1));
    if (!token)
    {
        fprintf(stderr, "Error de asignación de memoria.\n");
        exit(EXIT_FAILURE);
    }
    i = 0;
    while (start < end)
    {
        token[i++] = cpy_line[start++];
    }
    token[i] = '\0';
    
    return token;
}

char **ft_tokenize(t_general *g_data, int len)
{
    char **tokens;
    int i;
    int count;
    int start;
    char *delimiter;

    delimiter = " |<>";
    count = 0;
    start = 0;
    i = 0;
    tokens = malloc(sizeof(char *) * (len + 1));
    if (!tokens)
        exit(EXIT_FAILURE);
    while (i < len)
    {
        while (i < len && ft_strchr(delimiter, g_data->cpy_line[i]))
        {
            tokens[count] = ft_extract_token(g_data->cpy_line, i, i + 1);
            count++;
            i++;
        }
        if (i == len)
            break;
        start = i;
        while (i < len && !ft_strchr(delimiter, g_data->cpy_line[i]))
            i++;
        tokens[count] = ft_extract_token(g_data->cpy_line, start, i);
        count++;
    }
    tokens[count] = NULL;
    return tokens;
}

void    ft_quitar_comillas(char* cadena) //la usare despues de hacer la expansion
{
    int i;
    int j;
    int dentroComillas;
    
    i = 0;
    j = 0;
    if (cadena == NULL)
    {
        printf("Error: Cadena nula.\n");
        return;
    }
    dentroComillas = 0;
    while (cadena[i] != '\0')
    {
        if (cadena[i] == '\"' || cadena[i] == '\'')
        {
            dentroComillas = !dentroComillas; // Cambiar el estado si encontramos una comilla
        }
        else if (cadena[i] != ' ' || dentroComillas)
        {
            cadena[j] = cadena[i];
            j++;
        }
        i++;
    }
    cadena[j] = '\0';
}