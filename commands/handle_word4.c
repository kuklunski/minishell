/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 03:48:20 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/13 23:28:33 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	is_empty_var(t_token *token)
{
	if (token->type != VAR)
		return (false);
	if (token->str[0] != '\0')
		return (false);
	if (token->var_exists == true)
		return (false);
	return (true);
}

// if flag is true, which is set during quotes removal,
// we copy the joined vars as one arg
// and add the others as single args
static void	process_echo_arg(t_token **temp, char **args, int *i)
{
	if ((*temp)->join == true)
		args[*i] = join_vars(temp);
	else
		args[*i] = ft_strdup((*temp)->str);
	(*i)++;
	*temp = (*temp)->next;
}

void	remove_empty_args(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp->type == WORD || temp->type == VAR)
	{
		if (is_empty_var(temp))
		{
			temp = temp->next;
			if (temp == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			delete_token(temp->prev);
		}
		else
			temp = temp->next;
	}
}

// it removes empty args from the token list
// $foo does not exist, token will be "\0"
// count arguments : joined as one, not joined one by one
// allocates an args[command + args + NULL]
int	create_args_echo(t_token **token_node, t_command *last_cmd)
{
	int		nb_args;
	t_token	*temp;
	int		i;

	remove_empty_args(token_node);
	temp = *token_node;
	nb_args = count_arguments(temp);
	last_cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->args)
		return (FAILURE);
	i = 0;
	last_cmd->args[i] = ft_strdup(last_cmd->command);
	i++;
	while (temp->type == WORD || temp->type == VAR)
		process_echo_arg(&temp, last_cmd->args, &i);
	last_cmd->args[i] = NULL;
	*token_node = temp;
	return (SUCCESS);
}
