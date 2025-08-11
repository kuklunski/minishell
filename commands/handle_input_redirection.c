/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 01:11:21 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 22:57:37 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	remove_old_infile(t_io_fds *io)
{
	if (io->infile)
	{
		if (io->fd_in == -1 || (io->outfile && io->fd_out == -1))
			return (false);
		if (io->heredoc_delimiter != NULL)
		{
			free_ptr(io->heredoc_delimiter);
			io->heredoc_delimiter = NULL;
			unlink(io->infile);
		}
		free_ptr(io->infile);
		close(io->fd_in);
	}
	return (true);
}

// open_infile opens a file to read from (O_RDONLY)
// used for input redirection <.
// cat < input.txt
static void	open_infile(t_io_fds *io, char *file, char *filename)
{
	if (!remove_old_infile(io))
		return ;
	io->infile = ft_strdup(file);
	if (io->infile && io->infile[0] == '\0')
	{
		error_cmd(filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
	{
		error_cmd(io->infile, NULL, strerror(errno), false);
		return ;
	}
}

void	handle_input_redirection(t_command **cmd, t_token **tokens)
{
	t_token		*temp;
	t_command	*tcmd;

	temp = *tokens;
	tcmd = *cmd;
	while (tcmd->next != NULL)
		tcmd = tcmd->next;
	init_inf_outf(tcmd);
	open_infile(tcmd->io_fds, temp->next->str, temp->next->str_backup);
	temp = temp->next;
	if (temp->next->next)
		temp = temp->next->next;
	*tokens = temp;
}
