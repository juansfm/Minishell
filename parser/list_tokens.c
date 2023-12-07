/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agil-ord <agil-ord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:36:40 by agil-ord          #+#    #+#             */
/*   Updated: 2023/12/04 16:21:38 by agil-ord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_new_token(int type_token, char *value)
{
    int len;
    t_token *new_node;

	len = ft_strlen(value);
    new_node = (t_token *)malloc(sizeof(t_token));
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