/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 02:54:00 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 22:58:13 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	args(t_token *temp)
{
	int	counter;

	counter = 0;
	while (temp && (temp->type == WORD || temp->type == VAR))
	{
		counter++;
		temp = temp->next;
	}
	return (counter);
}

static void	copy_tokens_to_args(t_token **temp_ptr, t_command *l_cmd)
{
	int		i;
	t_token	*temp;

	temp = *temp_ptr;
	i = 0;
	l_cmd->args[i] = ft_strdup(l_cmd->command);
	i++;
	while (temp->type == WORD || temp->type == VAR)
	{
		l_cmd->args[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	l_cmd->args[i] = NULL;
	*temp_ptr = temp;
}

// copies the content of the tokens created to the command->args
// +2 cause the first one is the command name
// and the last one is NULL
int	create_args_def(t_token **tok, t_command *l_cmd)
{
	int		nb_args;
	t_token	*temp;

	temp = *tok;
	nb_args = args(temp);
	l_cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!l_cmd->args)
		return (FAILURE);
	copy_tokens_to_args(tok, l_cmd);
	return (SUCCESS);
}

// has two modes, echo or default
// If a variable like $HOME expands to "echo -n hello", then:
// splitted[0] = "echo" becomes the command
// create_args_from_split creates tokens for "-n" and "hello"
// fill_arguments is called,
// which creates initial args via create_args_echo_mode
// Later, if more tokens follow, add_args_echo_mode would be used
// same for other commands than echo
// special case for echo cause
// Echo might need to preserve some stuff differently
// than other commands
// count_arguments function moved to handle_word5.c to avoid duplication

int	fill_arguments(t_token **token, t_command *cmd)
{
	if (!ft_strcmp(cmd->command, "echo"))
	{
		if (!(cmd->args))
			return (create_args_echo(token, cmd));
		else
			return (add_args_echo(token, cmd));
	}
	else
	{
		if (!(cmd->args))
			return (create_args_def(token, cmd));
		else
			return (add_args_def(token, cmd));
	}
	return (SUCCESS);
}