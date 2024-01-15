#include "minishell.h"

char *ft_extract_token(char *cpy_line, int start, int end)
{
    int token_length;
    char *token; 
    int i;

    token_length = end - start;
    token = ft_calloc((token_length + 1), sizeof(char));
    if (!token)
    {
        fprintf(stderr, "Error de asignación de memoria.\n");
        exit(EXIT_FAILURE);
    }
    i = 0;
    while (start < end)
    {
        token[i++] = cpy_line[start++];
        printf("\nPROBANDO token[%d]: %c\n", i - 1, token[i - 1]);
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
    tokens = ft_calloc((len + 1), sizeof(char *));
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

void ft_quitar_comillas(char* cadena)
{
    int i = 0;
    int j = 0;
    int dentroComillas = 0;

    if (cadena == NULL)
    {
        printf("Error: Cadena nula.\n");
        return;
    }

    while (cadena[i] != '\0')
    {
        if (cadena[i] == '\"' || cadena[i] == '\'')
        {
            dentroComillas = !dentroComillas; // Cambiar el estado si encontramos una comilla
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

void ft_reordenar_palabras(char *cadena)//no se usa
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

char **ft_eliminar_espacios(char **cadena_de_cadenas)
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
        {
            cantidad_cadenas++;
        }
        i++;
    }

    resultado = ft_calloc((cantidad_cadenas + 1), sizeof(char *)); // Reservar memoria para el resultado
    if (!resultado)
    {
        return NULL; // Manejar error de asignación de memoria
    }

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