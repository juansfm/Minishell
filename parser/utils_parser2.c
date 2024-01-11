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

/*
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
*/

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
/*
void ft_eliminar_espacios(char *cadena)
{
    int k;
    int j;
    
    j = 0;
    k = 0;
    while (cadena[j] != '\0')
    {
        while (cadena[j] == ' ' && cadena[j + 1])
        {
            j++;
        }
        cadena[k++] = cadena[j++];
    }
    cadena[k] = '\0';
}

*/
void ft_reordenar_palabras(char *cadena)
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
/*
void ft_limpiar_espacios(char ***cadena_de_cadenas)
{
    int i;
    
    i = 0;
    while ((*cadena_de_cadenas)[i] != NULL)
    {
        ft_eliminar_espacios((*cadena_de_cadenas)[i]);
        ft_reordenar_palabras((*cadena_de_cadenas)[i]);
        i++;
    }
}
*/
/*
void eliminar_espacios(char **cadena_de_cadenas) {
    int i;
    int cantidad_cadenas;
    int j;
    // Contar la cantidad de cadenas válidas
    i = 0;
    cantidad_cadenas = 0;
    while (cadena_de_cadenas[i] != NULL)
    {
        if (ft_strcmp(cadena_de_cadenas[i], " ") != 0)
        {
            cantidad_cadenas++;
        }
        i++;
    }

    // Eliminar cadenas que contienen solo espacios
    i = 0;
    j = 0;
    while (cadena_de_cadenas[i] != NULL)
    {
        if (ft_strcmp(cadena_de_cadenas[i], " ") != 0)
        {
            cadena_de_cadenas[j] = cadena_de_cadenas[i];
            j++;
        }
        i++;
    }
    cadena_de_cadenas[cantidad_cadenas] = NULL; // Establecer el nuevo final del arreglo
}

char **ft_quita_quita(char **split_token)
{
    int i;
    int j;
    int num_word;
    int len_word;
    char **split_s_spacio;

    i = 0;
    j = 0;
    len_word = 0;
    num_word = 0;
    split_s_spacio = NULL;
    while (split_token[num_word] != NULL)
    {
        num_word++;
    }
    split_s_spacio = malloc(sizeof(char *) * (num_word + 1));
    if (!split_s_spacio)
        exit(EXIT_FAILURE);
    while(split_token[i])
    {
        len_word = ft_strlen(split_token[i]);
        if(split_token[i] && split_token[i + 1])
            i++;
        else
        {
            
            sp

            i++;
        }
    }
}
*/

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

    resultado = malloc((cantidad_cadenas + 1) * sizeof(char *)); // Reservar memoria para el resultado
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