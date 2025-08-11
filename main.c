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
		//set_signals();
		data->user_input = readline(">>>  Minishell>$");
		//set_signals();
		
		// Handle EOF (Ctrl+D)
		if (!data->user_input)
		{
			printf(" exit\n");
			break;
		}
		
		if (parsing(data) == true)
		{
			// TODO: execute commands
			//g_last_exit_code = execute(data);
		}
		else
		{
			//g_last_exit_code = 1;
		}
		free_iteration_data(data);  // Only free iteration-specific data
	}
	free_data(data);  // Free all remaining data at program exit
}

int main(int ac, char **av, char **env)
{
  t_data  data;
  
  set_to_zero(&data, sizeof(t_data));

  check_arguments(&data, ac, av);

  if (!init_data(&data, env))
  {
    //exit_shell_cleanly(&data);
    return 0;
  }
  //debug(env, &data);
  minishell(&data);
  return 0;
}