/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:41:14 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/07 23:41:14 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Helper function to fill token fields with provided values
static void	fill_token(t_token *token, char *str, char *str_backup, int type,
		int status)
{
	token->str = str;
	token->str_backup = str_backup;
	token->type = type;
	token->status = status;
}
static void	initialize_token(t_token *token)
{
	token->str = NULL;
	token->str_backup = NULL;
	token->var_exists = false;
	token->type = 0;
	token->status = 0;
	token->join = false;
	token->prev = NULL;
	token->next = NULL;
}

t_token	*create_token(char *str, char *str_backup, int type, int status)
{
	t_token *new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	initialize_token(new_node);
	fill_token(new_node, str, str_backup, type, status);
	return (new_node);
}