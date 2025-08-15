/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:16:09 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/09 21:16:09 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// handle_opening_quote
// if it encounters an opening quote, it sets the status to SQUOTE or DQUOTE
// and increments the index to skip it
static bool	h_o_quote(char *str, int *i, int *status)
{
	if ((str[*i] == '\'' || str[*i] == '\"') && *status == DEFAULT)
	{
		if (str[*i] == '\'')
			*status = SQUOTE;
		if (str[*i] == '\"')
			*status = DQUOTE;
		(*i)++;
		return (true);
	}
	return (false);
}

// handle_closing_quote
// if it encounters a closing quote, it sets the status to default
// and increments the index to skip it
static bool	h_c_quote(char *str, int *i, int *status)
{
	if ((str[*i] == '\'' && *status == SQUOTE) || (str[*i] == '\"'
			&& *status == DQUOTE))
	{
		*status = DEFAULT;
		(*i)++;
		return (true);
	}
	return (false);
}

int	len_no_quotes(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i])
	{
		if (h_o_quote(str, &i, &status))
			continue ;
		else if (h_c_quote(str, &i, &status))
			continue ;
		count++;
		i++;
	}
	return (count + 1);
}

// we first count the length of the string without quotes
// copy the characters to a new allocated string without quotes,
// free the old string and set the new string to the token
int	then_remove_quotes(t_token **token)
{
	char *new_line;
	int len;

	len = len_no_quotes((*token)->str, 0, 0);
	new_line = malloc(sizeof(char) * len);
	if (!new_line)
		return (1);
	copy_new_line(token, new_line);
	free_ptr((*token)->str);
	(*token)->str = new_line;
	(*token)->join = true;
	return (0);
}