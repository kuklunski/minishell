/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 04:21:01 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/14 00:28:46 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free_ptr(tab[i]);
		i++;
	}
	free_ptr(tab);
}

// Free data that should be cleaned up after each command iteration
void	free_iteration_data(t_data *data)
{
	if (!data)
		return ;
	if (data->user_input)
	{
		free_ptr(data->user_input);
		data->user_input = NULL;
	}
	if (data->token)
	{
		free_tokens(&data->token);
		data->token = NULL;
	}
}

void	free_data_cleanup(t_data *data)
{
	if (!data)
		return ;
	free_iteration_data(data);
	if (data->cmd)
	{
		free_commands(&data->cmd);
		data->cmd = NULL;
	}
	if (data->env)
	{
		free_env(data);
		data->env = NULL;
	}
	if (data->working_dir)
	{
		free_ptr(data->working_dir);
		data->working_dir = NULL;
	}
	if (data->old_working_dir)
	{
		free_ptr(data->old_working_dir);
		data->old_working_dir = NULL;
	}
}
