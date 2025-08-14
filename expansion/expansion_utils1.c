/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:56:04 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/13 23:50:17 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// used to remove backslash from the string
void	remove_char_at_index(char **str, int index)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(*str);
	new_str = malloc(len);
	if (!new_str)
		return ;
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if (i != index)
			new_str[j++] = (*str)[i];
		i++;
	}
	new_str[j] = '\0';
	free(*str);
	*str = new_str;
}

// function to get the value of the variable from **env
char	*get_var_value(t_token *token, char *str, t_data *data)
{
	char	*value;
	char	*var;

	var = get_var_name(str);
	if (!var)
		return (NULL);
	if (var && var[0] == '?' && var[1] == '=')
		value = ft_itoa(g_last_exit_code);
	else
	{
		value = extract_var_env(data, var);
		if (value && token != NULL)
			token->var_exists = true;
	}
	free_ptr(var);
	return (value);
}

// function to get the variable name from the token
char	*get_var_name(char *str)
{
	int		start;
	char	*result;

	start = find_dollar_pos(str);
	result = add_equals(str, start);
	return (result);
}
