/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:40:59 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/13 23:48:09 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to check if a variable is inside quotes
bool	var_inside_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (true);
		else
			return (false);
	}
	return (false);
}

// checks if the character is a valid start for a variable name
bool	valid_var_start(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (true);
	return (false);
}

// checks if the character is a special variable like $?
bool	is_special_var(char c)
{
	if (c == '?' || (c >= '0' && c <= '9'))
		return (true);
	return (false);
}

// checks if the next character is a separator
// a separator is a character that indicates the end of a variable name
bool	check_next_sep(char c)
{
	if (c == ' ' || c == '=' || c == '\0' || c == ':' || c == '|' || c == '&'
		|| c == ';' || c == '(' || c == ')' || c == '<' || c == '>' || c == '\t'
		|| c == '\n' || c == '$')
		return (true);
	else
		return (false);
}

void	update_status(t_token **node, char c)
{
	if (c == '\'' && (*node)->status == DEFAULT)
		(*node)->status = SQUOTE;
	else if (c == '\"' && (*node)->status == DEFAULT)
		(*node)->status = DQUOTE;
	else if (c == '\'' && (*node)->status == SQUOTE)
		(*node)->status = DEFAULT;
	else if (c == '\"' && (*node)->status == DQUOTE)
		(*node)->status = DEFAULT;
}
