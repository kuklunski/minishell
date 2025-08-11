/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:50:15 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/11 00:06:07 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	should_expand_heredoc_var(char *str, int i)
{
	if (str[i] != '$')
		return (0);
	if (!valid_var_start(str[i + 1]) && !is_special_var(str[i + 1]))
		return (0);
	if (check_next_sep(str[i + 1]) == true)
		return (0);
	if (var_inside_quotes(str, i) == true)
		return (0);
	return (1);
}

static void	process_heredoc_expansion(char **str, t_data *data, int *i)
{
	char	*var_value;

	if (should_expand_heredoc_var(*str, *i))
	{
		var_value = get_var_value(NULL, *str + *i, data);
		*str = replace_var_heredoc(*str, var_value, *i);
	}
	else
		(*i)++;
}

char	*expansion_heredoc(t_data *data, char *str)
{
	int i;

	i = 0;
	while (str[i])
		process_heredoc_expansion(&str, data, &i);
	return (str);
}