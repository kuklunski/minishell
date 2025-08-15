/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:48:10 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/13 23:49:57 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	valid_name(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || c == '_')
		return (true);
	else
		return (false);
}

int	count_var_chars(char *str, int start)
{
	int	count;
	int	i;

	count = 0;
	i = start;
	while (str[i])
	{
		if (valid_name(str[i]) == false)
			break ;
		count++;
		i++;
	}
	return (count);
}

// finds the position of the first '$' in the string
int	find_dollar_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

// function to return how many characters after '$' $home = 4
int	var_end(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '$')
		i++;
	i++;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
		return (count + 1);
	return (count_var_chars(str, i));
}

// extracts the variable name from the string starting from the position of '$'
// and adds '=' sign at the end
// to search inside the env with "var="
char	*add_equals(char *str, int start)
{
	char	*var;
	char	*tmp;
	int		len;

	len = var_end(str);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	free_ptr(var);
	return (tmp);
}
