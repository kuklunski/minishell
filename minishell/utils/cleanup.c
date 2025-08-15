/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yofouzi <yofouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:33:27 by yofouzi           #+#    #+#             */
/*   Updated: 2025/08/14 13:33:28 by yofouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_io(t_io_fds *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->heredoc_delimiter)
	{
		unlink(io->infile);
		free_ptr(io->heredoc_delimiter);
	}
	if (io->infile)
		free_ptr(io->infile);
	if (io->outfile)
		free_ptr(io->outfile);
	if (io)
		free_ptr(io);
}

void	delete_cmd_list(t_command *cmd)
{
	if (!cmd)
        return;
	if (cmd->command)
		free(cmd->command);
	if (cmd->args)
		free_str_tab(cmd->args);
	if (cmd->pipe_fd)
		free_ptr(cmd->pipe_fd);
	if (cmd->io_fds)
		free_io(cmd->io_fds);
	free_ptr(cmd);
}

// it passes the next->cmd to temp to keep track of it
// cleans current cmd, and gets cmd->next by temp
// to clear it next
void	clear_cmd_list(t_command **cmd)
{
	t_command	*temp;

	temp = NULL;
	while(*cmd != NULL)
	{
		temp = (*cmd)->next;
		delete_cmd_list(*cmd);
		*cmd = temp;
	}
}

void	close_fds(t_command *cmds, bool close_backups)
{
	if (cmds->io_fds)
	{
		if (cmds->io_fds->fd_in != -1)
			close(cmds->io_fds->fd_in);
		if (cmds->io_fds->fd_out != -1)
			close(cmds->io_fds->fd_out);
		if (close_backups)
			restore_io(cmds->io_fds);
	}
	close_pipe_fds(cmds, NULL);
}
