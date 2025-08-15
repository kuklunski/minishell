/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_with_no_args.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 04:28:25 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 22:57:30 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Helper function to create args array for command with no arguments
static char	**create_single_arg(char *command)
{
	char	**args;

	args = malloc(sizeof(char *) * 2);
	if (!args)
		return (NULL);
	args[0] = ft_strdup(command);
	args[1] = NULL;
	return (args);
}

static bool	needs_args_array(t_command *cmd)
{
	if (!cmd)
		return (false);
	return (cmd->command && !cmd->args);
}

// if cmd->args does not exist, we create it
// and pass it to create_single_arg
// else move on
void	commands_with_no_args(t_data *data)
{
	t_command	*cmd;

	if (!data || !data->cmd)
		return ;
	cmd = data->cmd;
	while (cmd)
	{
		if (needs_args_array(cmd))
			cmd->args = create_single_arg(cmd->command);
		cmd = cmd->next;
	}
}
