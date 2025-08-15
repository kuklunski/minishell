/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yofouzi <yofouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:31:37 by yofouzi           #+#    #+#             */
/*   Updated: 2025/08/14 13:34:36 by yofouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_builtin(t_data *data, char **args)
{
	int	i;

	if (args && args[1])
		return (error_cmd("env", NULL, "too many arguments", 2));
	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
		ft_putendl_fd(data->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	env_builtin_export(t_data *data, char **args)
{
	int	i;

	if (args && args[1])
		return (error_cmd("env", NULL, "too many arguments", 2));
	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
	{
		printf("declare -x ");
		printf("%s\n", data->env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
