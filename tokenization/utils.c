/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:15:37 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/11 01:03:56 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_token_type(char c, char cc)
{
	if (((c > 8 && c < 14) || c == 32))
		return (SPACES);
	else if (c == '|')
		return (PIPE);
	else if (c == '<' && cc == '<')
		return (HEREDOC);
	else if (c == '>' && cc == '>')
		return (APPEND);
	else if (c == '<')
		return (INPUT);
	else if (c == '>')
		return (TRUNC);
	else if (c == '\0')
		return (END);
	else
		return (0);
}

int	save_token(int *i, char *str, int start, t_data *data)
{
	int		type;
	int		j;
	char	c;
	char	cc;

	j = *i;
	c = str[j];
	cc = (str[j] != '\0') ? str[j + 1] : '\0';
	type = get_token_type(c, cc);
	if (type)
		start = process_type(i, str, start, data, type);
	return (start);
}

int	put_flag(int flag, char *str, int i)
{
	if (str[i] == '\'' && flag == DEFAULT)
		flag = SQUOTE;
	else if (str[i] == '\"' && flag == DEFAULT)
		flag = DQUOTE;
	else if (str[i] == '\'' && flag == SQUOTE)
		flag = DEFAULT;
	else if (str[i] == '\"' && flag == DQUOTE)
		flag = DEFAULT;
	return (flag);
}
