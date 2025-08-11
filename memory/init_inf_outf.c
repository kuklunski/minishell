/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inf_outf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 04:35:41 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 04:35:41 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_inf_outf(t_command *command)
{
	if (!command->io_fds)
	{
		command->io_fds = malloc(sizeof *command->io_fds);
		if (!command->io_fds)
			return ;
		command->io_fds->infile = NULL;
		command->io_fds->outfile = NULL;
		command->io_fds->heredoc_delimiter = NULL;
		command->io_fds->heredoc_quotes = false;
		command->io_fds->fd_in = -1;
		command->io_fds->fd_out = -1;
		command->io_fds->stdin_backup = -1;
		command->io_fds->stdout_backup = -1;
	}
}