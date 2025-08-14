/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:55:31 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/13 23:50:37 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// extracts the value of the var from the **env
char	*extract_var_env(t_data *data, char *var)
{
	char	*str;
	int		i;
	int		len;

	if (!var)
		return (NULL);
	i = 0;
	len = ft_strlen(var);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var, len) == 0)
			break ;
		i++;
	}
	if (data->env[i] == NULL)
		return (NULL);
	str = ft_strdup(data->env[i] + len);
	return (str);
}
