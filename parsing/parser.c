/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:07:46 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/11 04:17:38 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/////////////////////////////debug
static void	print_commands(t_command *cmd)
{
	int i;

	if (!cmd)
	{
		printf("No commands to display.\n");
		return;
	}
	while (cmd)
	{
		printf("------------ COMMAND NODE ------------\n");
		printf("Command    : %s\n", cmd->command ? cmd->command : "NULL");

		// Print arguments
		printf("Args       : ");
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				printf("%s ", cmd->args[i]);
				i++;
			}
			printf("\n");
		}
		else
			printf("NULL\n");
		cmd = cmd->next;
	}
}

bool	parsing(t_data *data)
{
	int check_result;

	check_result = first_step(data);
	if (check_result == 0)
		return (false);
	if (check_result == 2)
		return (true);
	add_history(data->user_input);
	if (second_step(data) == false)
		return (false);
	third_step(data);
	printf("\nafter create commands \n");
	printf("\nafter create commands \n");
	print_commands(data->cmd);//debug
	return (true);
}