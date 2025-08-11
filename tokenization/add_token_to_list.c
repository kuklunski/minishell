/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_to_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:49:20 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/07 23:49:20 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Helper function to find the last token in the linked list
static t_token	*get_last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

// Adds a new token to the end of the token list
// Creates a doubly-linked list structure
void	add_token_to_list(t_token **list, t_token *new_node)
{
	t_token *last;

	if (!*list)
	{
		*list = new_node;
		return ;
	}
	last = get_last_token(*list);
	last->next = new_node;
	new_node->prev = last;
}