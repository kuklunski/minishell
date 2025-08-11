/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_or_consecutive_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 03:19:09 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/08 03:19:09 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// checks if we have two consecutive pipes or redirections
static bool	check_redir(t_token *token)
{
	if (token->prev)
	{
		if (token->type == PIPE && token->prev->type == PIPE)
			return (true);
		if (token->type > PIPE && token->prev->type > PIPE)
			return (true);
		if (token->type == END && token->prev->type >= PIPE)
			return (true);
	}
	return (false);
}

//
// Handles error messages specifically for END tokens
// - "ls >" -> "newline" as the unexpected token
// - "ls |" -> "|" as the unexpected token
//
static void	handle_end_token_error(t_token *temp)
{
	if (temp->prev && temp->prev->type > PIPE)
		error_msg("syntax error near unexpected token", "newline", true);
	else if (temp->prev)
		error_msg("syntax error near unexpected token", temp->prev->str, true);
}

//
// Processes a single token for syntax validation
// Examples:
// - Valid: "ls > file" → returns SUCCESS
// - Invalid: "ls > >" → calls handle_syntax_error and returns FAILURE
// - Invalid: "ls |" → calls handle_syntax_error and returns FAILURE
// Combines syntax checking with error reporting for one token
//
static int	process_token_check(t_token *temp)
{
	if (check_redir(temp) == true)
	{
		if (temp->type == END)
			handle_end_token_error(temp);
		else
			error_msg("syntax error near unexpected token", temp->str, true);
		return (FAILURE);
	}
	return (SUCCESS);
}

//
// Validates syntax of entire token list for consecutive operators
// Examples of invalid input that would return FAILURE:
// - "ls | | wc" (consecutive pipes)
// - "cat < < file" (consecutive input redirections)
// - "echo hello >" (incomplete redirection)
// - "ls |" (pipe without command)
// Returns SUCCESS if all tokens are syntactically valid, FAILURE on first error
//
int	check_consecutives(t_token **token_lst)
{
	t_token *temp;

	temp = *token_lst;
	while (temp)
	{
		if (process_token_check(temp) == FAILURE)
			return (FAILURE);
		temp = temp->next;
	}
	return (SUCCESS);
}