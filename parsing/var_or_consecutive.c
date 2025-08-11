/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_or_consecutive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 03:16:22 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/08 03:16:22 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	put_type_var(t_token **token_node)
{
	int	i;

	i = 0;
	while ((*token_node)->str[i])
	{
		if ((*token_node)->str[i] == '$')
		{
			if ((*token_node)->prev && (*token_node)->prev->type == HEREDOC)
				break ;
			(*token_node)->type = VAR;
			return ;
		}
		i++;
	}
}

int	var_or_consecutive(t_token **token_lst)
{
	t_token *temp;

	temp = *token_lst;
	if (temp->type == PIPE)
	{
		error_msg("syntax error near unexpected token", temp->str, true);
		return (FAILURE);
	}
	while (temp)
	{
		put_type_var(&temp);
		if (check_consecutives(&temp) == FAILURE)
			return (FAILURE);
		temp = temp->next;
	}
	return (SUCCESS);
}