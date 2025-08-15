/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:16:48 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 21:16:48 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell(t_data *data)
{
	while (1)
	{
		set_signals_parent();
		data->user_input = readline(PROMPT);
		set_signals_child();
		if (parsing(data) == true)
			g_last_exit_code = execute(data);
		else
			g_last_exit_code = 1;
		free_data(data, false);
	}
	free_data_cleanup(data);
}

int main(int ac, char **av, char **env)
{
  t_data  data;
  
  (void)ac;
  (void)av;
  set_to_zero(&data, sizeof(t_data));
  if (!init_data(&data, env))
  {
    exit_shell(NULL, EXIT_FAILURE);
    return 0;
  }
  //debug(env, &data);
  minishell(&data);
  exit_shell(&data, g_last_exit_code);
  return 0;
}