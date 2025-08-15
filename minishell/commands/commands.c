/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:51:07 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/15 18:35:30 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	parse_token(t_data *data, t_token **temp)
{
	if ((*temp)->type == INPUT)
		handle_input_redirection(&data->cmd, temp);
	else if ((*temp)->type == TRUNC)
		handle_trunc_redirection(&data->cmd, temp);
	else if ((*temp)->type == APPEND)
		handle_append(&data->cmd, temp);
	else if ((*temp)->type == PIPE)
		handle_pipe(&data->cmd, temp);
	else if ((*temp)->type == WORD || (*temp)->type == VAR)
		handle_word_var(&data->cmd, temp);
	else if ((*temp)->type == HEREDOC)
		handle_heredoc(&data->cmd, temp, data);
	else if ((*temp)->type == END)
		return ;
}

void	create_commands(t_data *data)
{
	t_token	*temp;

	temp = data->token;
	if (temp->type == END)
		return ;
	while (temp && temp->type != END)
	{
		//printf("create_commands: %s token type %d\n", temp->str, temp->type);
		if (temp == data->token)
			cmd_list_append(&data->cmd, false);
		parse_token(data, &temp);
	}
	commands_with_no_args(data);
}
