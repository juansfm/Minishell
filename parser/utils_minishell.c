#include "minishell.h"

t_cmd *ft_create_new_cmd(void)
{
    t_cmd *new_cmd = ft_calloc(sizeof(t_cmd), 1);
    new_cmd->infile = 0;
    new_cmd->outfile = 0;
    new_cmd->next = NULL;
    return new_cmd;
}
char **ft_convert_token_list_to_array(t_token *token_list)
{
    // Contar el número de tokens
    int count = 0;
    int i;
    char **array;
    t_token *current = token_list;
    while (current)
    {
        count++;
        current = current->next;
    }

    // Crear un array de cadenas
    array = ft_calloc(sizeof(char *), (count + 1));
    if (!array) {
        return NULL;  // Error de asignación de memoria
    }

    // Llenar el array con los valores de los tokens
    current = token_list;
    i = 0;
    while (i < count) 
    {
        array[i] = ft_strdup(current->value);
        current = current->next;
        i++;
    }
    // El último elemento debe ser NULL
    array[count] = NULL;

    return array;
}
/*
*/