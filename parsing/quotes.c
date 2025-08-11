/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:10:28 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 22:58:17 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Logic:
// 1. If no quotes exist -> don't remove (nothing to remove)
// 2. If token is at start of list -> remove quotes (normal processing)
// 3. If previous token is not HEREDOC -> remove quotes (normal processing)  
// 4. If previous token is HEREDOC -> keep quotes (heredoc delimiter should preserve quotes)
static bool	should_remove_quotes(t_token *token, bool has_quotes)
{
	if (!has_quotes)
		return (false);
	if (!token->prev)
		return (true);
	if (token->prev->type != HEREDOC)
		return (true);
	return (false);
}

int	parse_quotes(t_data *data)
{
	t_token *temp;
	int i;
	bool has_quotes;

	temp = data->token;
	while (temp)
	{
		has_quotes = false;
		i = 0;
		while (temp->str[i])
		{
			if (temp->str[i] == '\'' || temp->str[i] == '\"')
			{
				has_quotes = true;
				break ;
			}
			i++;
		}
		if (should_remove_quotes(temp, has_quotes))
			then_remove_quotes(&temp);
		temp = temp->next;
	}
	return (0);
}