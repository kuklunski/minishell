/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:51:24 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/13 23:47:29 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	should_expand_var(t_token *token, int i)
{
	if (token->str[i] == '$'
		&& check_next_sep(token->str[i + 1]) == false
		&& var_inside_quotes(token->str, i) == false
		&& (token->status == DEFAULT || token->status == DQUOTE))
		return (1);
	return (0);
}

static void	process_var_expansion(t_token **token, t_data *data, int *i)
{
	char	*var_value;

	if (should_expand_var(*token, *i))
	{
		var_value = get_var_value(*token, (*token)->str + *i, data);
		replace_var(token, (*token)->str, var_value, *i);
		free_ptr(var_value);
	}
	else
		(*i)++;
}

static void	expand_token_vars(t_token **token, t_data *data)
{
	int	i;

	i = 0;
	while ((*token)->str[i])
	{
		update_status(token, (*token)->str[i]);
		process_var_expansion(token, data, &i);
	}
}

int	expansion(t_data *data, t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	while (temp)
	{
		if (temp->type == VAR)
			expand_token_vars(&temp, data);
		temp = temp->next;
	}
	return (0);
}
