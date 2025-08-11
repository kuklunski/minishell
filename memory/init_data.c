/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:12:00 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 21:12:00 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool    init_env(t_data *data, char **env)
{
    int i;

    i = 0;
    if (!env)
        return (false);
    while (env && env[i])
        i++;
    data->env = ft_calloc(i + 1, sizeof(char *));
    if (!data->env)
        return (false);
    i = 0;
    while (env[i])
    {
      data->env[i] = ft_strdup(env[i]);
      if (!data->env[i]) {
        while (--i >= 0)
          free_ptr(data->env[i]);
        free_ptr(data->env);
        return (false);
      }
      i++;
    }
    return (true);
}

bool    init_data(t_data *data, char **env)
{
    if (!init_env(data, env))
	{
		write(STDERR_FILENO, "failed to set up environment\n", ft_strlen("failed to set up environment\n"));
		return (false);
	}
	if (!init_working_dirs(data))
	{
		write(STDERR_FILENO, "failed to set up working directories\n", ft_strlen("failed to set up working directories\n"));
		// Clean up environment on working dir failure
		if (data->env)
		{
			int i = 0;
			while (data->env[i])
			{
				free_ptr(data->env[i]);
				i++;
			}
			free_ptr(data->env);
			data->env = NULL;
		}
		return (false);
	}
	data->token = NULL;
	data->user_input = NULL;
	data->cmd = NULL;
	data->pid = -1;
	g_last_exit_code = 0;
	return (true);
}