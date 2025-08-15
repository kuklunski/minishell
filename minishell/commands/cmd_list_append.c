/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:55:52 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 00:55:52 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*cmd_list_append(t_command **cmd, bool flag)
{
	t_command	*new_node;
	t_command	*start;

	new_node = (t_command *)malloc(sizeof(t_command));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_command));
	new_node->pipe_output = flag;
	if (*cmd == NULL)
	{
		*cmd = new_node;
		return (new_node);
	}
	start = *cmd;
	while (start->next)
		start = start->next;
	start->next = new_node;
	new_node->prev = start;
	return (new_node);
}
