/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 01:21:57 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/15 17:12:53 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Remove the old file if it exists
static bool	remove_old_file(t_io_fds *io)
{
	if (io->outfile)
	{
		if (io->fd_out == -1 || (io->infile && io->fd_in == -1))
			return (false);
		free_ptr(io->outfile);
		close(io->fd_out);
	}
	return (true);
}

// Open file for appending
// If the file already exists, it will be opened in append mode
static void	open_file_append(t_io_fds *io, char *file, char *str_backup)
{
	if (!remove_old_file(io))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0' && str_backup)
	{
		error_cmd(str_backup, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->fd_out == -1)
	{
		error_cmd(io->outfile, NULL, strerror(errno), false);
		return ;
	}
}

// Handle append redirection
// It appends the file to the command's output
// It expects the next token to be the file name
// It updates the token list to skip the file name token
void	handle_append(t_command **cmd, t_token **tokens)
{
	t_command	*tcmd;
	t_token		*temp;

	temp = *tokens;
	tcmd = *cmd;
	while (tcmd->next != NULL)
		tcmd = tcmd->next;
	init_inf_outf(tcmd);
	open_file_append(tcmd->io_fds, temp->next->str, temp->next->str_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*tokens = temp;
}
