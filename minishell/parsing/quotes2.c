/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:39:57 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 22:58:17 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// handle_quote_status changes: true = enter quote, false = exit quote
static bool	h_q_stat(t_token **tok, int *i, bool quote, char c)
{
	if (quote)
	{
		if ((c == '\'' || c == '\"') && (*tok)->status == DEFAULT)
		{
			if (c == '\'')
				(*tok)->status = SQUOTE;
			else
				(*tok)->status = DQUOTE;
			(*i)++;
			return (true);
		}
	}
	else
	{
		if ((c == '\'' && (*tok)->status == SQUOTE) || (c == '\"'
				&& (*tok)->status == DQUOTE))
		{
			(*tok)->status = DEFAULT;
			(*i)++;
			return (true);
		}
	}
	return (false);
}

// copy characters to a new allocated string,
// with the new calculated length without quotes,
// first with h_q_stat as true,
// we enter quotes and set status to SQUOTE or DQUOTE
// then with h_q_stat as false, we exit quotes and set status to DEFAULT
// while incrementing the index to skip the quotes ofcourse
void
	copy_new_line(t_token **token, char *new_line)
{
	int i;
	int j;
	char c;

	i = 0;
	j = 0;
	while ((*token)->str[i])
	{
		c = (*token)->str[i];
		if (h_q_stat(token, &i, true, c))
			continue ;
		else if (h_q_stat(token, &i, false, c))
			continue ;
		new_line[j++] = (*token)->str[i++];
	}
	new_line[j] = '\0';
}