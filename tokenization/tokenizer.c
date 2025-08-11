/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:23:58 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/07 22:23:58 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_final_flag(int flag)
{
	if (flag != DEFAULT)
	{
		if (flag == DQUOTE)
			error_msg("unexpected EOF while looking for matching", "\"", true);
		else if (flag == SQUOTE)
			error_msg("unexpected EOF while looking for matching", "\'", true);
		error_msg("syntax error", "unexpected end of file", false);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	process_input_tokens(t_data *data, int len)
{
	int	i;
	int	token_start;
	int	flag;

	i = 0;
	token_start = 0;
	flag = DEFAULT;
	while (i <= len)
	{
		flag = put_flag(flag, data->user_input, i);
		if (flag == DEFAULT)
			token_start = save_token(&i, data->user_input, token_start, data);
		i++;
	}
	return (flag);
}

int	tokenizer(t_data *data)
{
	int len;
	int final_flag;

	len = ft_strlen(data->user_input);
	final_flag = process_input_tokens(data, len);
	return (check_final_flag(final_flag));
}