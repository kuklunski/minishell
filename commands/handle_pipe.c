/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 01:23:03 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 18:59:02 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pipe(t_command **cmd, t_token **tokens)
{
	t_command	*tcmd;
	t_token		*temp;

	temp = *tokens;
	tcmd = *cmd;
	while (tcmd->next != NULL)
		tcmd = tcmd->next;
	tcmd->pipe_output = true;
	cmd_list_append(&tcmd, false);
	temp = temp->next;
	*tokens = temp;
}
