/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 01:31:47 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 22:58:11 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	has_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

// check if token is var type and contains space
static bool	is_var_with_space(t_token *temp)
{
	if (temp->type == VAR && has_space(temp->str))
		return (true);
	return (false);
}

// check if token is start of new command (first token, after pipe, or no cmd)
static bool	is_command_new(t_token *temp, t_command *last_cmd)
{
	if (temp->prev == NULL)
		return (true);
	if (temp->prev && temp->prev->type == PIPE)
		return (true);
	if (last_cmd->command == NULL)
		return (true);
	return (false);
}

// if command is new,
//so that we dont split a token thats supposed to be an arg to a command
// example: echo "$home",
//$home is an arg and should be instead moved to fill_args
// check if it has var with space
// if yes split, if not, copy the content of token to ->command
static void	handle_command_token(t_token **t, t_command *l_cmd)
{
	if (is_command_new(*t, l_cmd))
	{
		if (is_var_with_space(*t))
			split_token(l_cmd, (*t)->str);
		else
			l_cmd->command = ft_strdup((*t)->str);
		*t = (*t)->next;
		return ;
	}
	fill_arguments(t, l_cmd);
}

// advance the token list to the last command to be processed
void	handle_word_var(t_command **cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*l_cmd;

	temp = *token_lst;
	while (temp->type == WORD || temp->type == VAR)
	{
		l_cmd = *cmd;
		while (l_cmd->next != NULL)
			l_cmd = l_cmd->next;
		handle_command_token(&temp, l_cmd);
	}
	*token_lst = temp;
}
