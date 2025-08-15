/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:32:56 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/07 23:32:56 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_not_separator(char prev_c, char curr_c)
{
	if (((prev_c > 8 && prev_c < 14) || prev_c == 32) || prev_c == '|'
		|| (prev_c == '<' && curr_c == '<') || (prev_c == '>' && curr_c == '>')
		|| prev_c == '<' || prev_c == '>' || prev_c == '\0')
		return (0);
	return (1);
}

static int	is_processable_type(int type)
{
	return (type == APPEND || type == HEREDOC || type == PIPE || type == INPUT
		|| type == TRUNC || type == END);
}

int	process_type(int *i, char *str, int start, t_data *data, int type)
{
	char prev_c;
	char curr_c;

	if ((*i) != 0)
	{
		prev_c = str[*i - 1];
		curr_c = str[*i];
		if (is_not_separator(prev_c, curr_c))
			token_word(&data->token, str, (*i), start);
	}
	if (is_processable_type(type))
	{
		token_separator(&data->token, str, (*i), type);
		if (type == APPEND || type == HEREDOC)
			(*i)++;
	}
	return ((*i) + 1);
}