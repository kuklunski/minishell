/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:58:18 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/13 23:43:07 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	calculate_replacement_size(char *str, char *var, int i)
{
	int	original_len;
	int	var_len;
	int	replacement_len;

	original_len = ft_strlen(str);
	var_len = var_end(str + i);
	replacement_len = ft_strlen(var);
	return (original_len - var_len + replacement_len);
}

static void	update_token_string(t_token **token, char *newstr)
{
	if (token && *token)
	{
		free_ptr((*token)->str);
		(*token)->str = newstr;
	}
}

char	*replace_var(t_token **token, char *str, char *var, int i)
{
	char	*newstr;
	int		newstr_size;

	newstr_size = calculate_replacement_size(str, var, i);
	newstr = new_token_string(str, var, newstr_size, i);
	update_token_string(token, newstr);
	return (newstr);
}
