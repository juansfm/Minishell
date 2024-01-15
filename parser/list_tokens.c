#include "minishell.h"

void ft_print_tokens(t_token *head) 
{
    while (head != NULL) 
    {
        printf("Token Type: %d, Value: %s\n", head->type_token, head->value);
        head = head->next;
    }
}


int ft_get_token_type(char *value)
{
    if (ft_strcmp(value, "|") == 0)
        return TOKEN_PIPE;
    else if (ft_strcmp(value, "<") == 0)
        return TOKEN__IN;
    else if (ft_strcmp(value, ">") == 0)
        return TOKEN__OUT;
    else if (ft_strcmp(value, "<<") == 0)
        return TOKEN_HERE_DOC_IN;
    else if (ft_strcmp(value, ">>") == 0)
        return TOKEN_HERE_DOC_OUT;
    else if (ft_strchr(value, '=') != NULL)
        return TOKEN__ARG;
    else
        return TOKEN_CMD;
}

t_token *ft_new_token(char *value)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = ft_strdup(value);
    token->len = ft_strlen(value);
    token->type_token = ft_get_token_type(value);
    token->next = NULL;
    return token;
}

t_token *ft_convert_to_tokens(char **str)
{
    t_token *head = NULL;
    t_token *current = NULL;
    char *token;
	int i = 0;
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

    return head;
}
/*
t_token *ft_new_token(int type_token, char *value)
{
    int len;
    t_token *new_node;

	len = ft_strlen(value);
    new_node = ft_calloc(1, sizeof(t_token));
    if (new_node == NULL)
    {
        printf("Error: No se pudo asignar memoria para el nuevo nodo.\n");
        return NULL;
    }

    new_node->len = len;
    new_node->type_token = type_token;
    new_node->value = ft_strdup(value);
    new_node->next = NULL;

    return (new_node);
}

// Función que añade un nuevo token a la lista dentro de t_general
void ft_add_token_in_general(t_token **head, int type_token, char *value)
{
    t_token *new_node;

    new_node = NULL;
	new_node = ft_new_token(type_token, value);
    if (new_node == NULL)
    {
        printf("Error: No se pudo crear el nuevo token.\n");
        return;
    }
    if (*head == NULL)
    {
        *head = new_node; // Si es el primer nodo, asigna el nuevo nodo como cabeza de la lista
    }
    else
    {
        t_token *current = *head;
        while (current->next != NULL)
        {
            current = current->next; // Avanza al último nodo
        }
        current->next = new_node; // Agrega el nuevo nodo al final de la lista
    }
}

void ft_free_tokens(t_token *head) 
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