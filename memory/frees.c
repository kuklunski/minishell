/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 04:45:54 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/14 00:27:10 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free_ptr(env[i]);
		i++;
	}
	free_ptr(env);
}

static void	free_tokens(t_token **head)
{
	t_token	*current;
	t_token	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		free_ptr(current->str);
		free_ptr(current->str_backup);
		free_ptr(current);
		current = next;
	}
	*head = NULL;
}

// avoid accidental double free
void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_command(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->command)
		free_ptr(cmd->command);
	if (cmd->args)
	{
		while (cmd->args[i] != NULL)
		{
			free_ptr(cmd->args[i]);
			i++;
		}
		free_ptr(cmd->args);
	}
	free_ptr(cmd);
}

void	free_commands(t_command **cmd_list)
{
	t_command	*tmp;

	while (*cmd_list)
	{
		tmp = (*cmd_list)->next;
		free_command(*cmd_list);
		*cmd_list = tmp;
	}
	*cmd_list = NULL;
}
