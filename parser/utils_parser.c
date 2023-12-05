/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agil-ord <agil-ord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:23:51 by agil-ord          #+#    #+#             */
/*   Updated: 2023/12/04 16:29:17 by agil-ord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_char_reserved(char c)
{
    if(c == ' ' || c == '|' || c == '>' || c == '<' || c == '\"' || c == '\'')
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
