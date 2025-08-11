/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:47:34 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 23:29:06 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expand_var(t_token **token, char *var_value, int i)
{
	if (var_value == NULL)
	{
		if (delete_var(token, (*token)->str, i) == 1)
		{
			return (1);
		}
	}
	else
	{
		if (!replace_var(token, (*token)->str, var_value, i))
		{
			free_ptr(var_value);
			return (1);
		}
	}
	free_ptr(var_value);
	return (0);
}