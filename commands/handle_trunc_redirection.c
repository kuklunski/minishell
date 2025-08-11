/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_trunc_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 01:18:07 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 22:58:08 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

// opens a file to write to, with flags like
// O_WRONLY | O_CREAT | O_TRUNC, used for output redirection >.
// echo "hello" > output.txt
static void	open_output_truncation(t_io_fds *io, char *file, char *filename)
{
	if (!remove_old_file(io))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0')
	{
		error_cmd(filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_out == -1)
	{
		error_cmd(io->outfile, NULL, strerror(errno), false);
		return ;
	}
}

void	handle_trunc_redirection(t_command **cmd, t_token **tokens)
{
	t_token		*temp;
	t_command	*tcmd;

	temp = *tokens;
	tcmd = *cmd;
	while (tcmd->next != NULL)
		tcmd = tcmd->next;
	init_inf_outf(tcmd);
	open_output_truncation(tcmd->io_fds, temp->next->str, temp->next->str_backup);
	temp = temp->next;
	if (temp->next->next)
		temp = temp->next->next;
	*tokens = temp;
}
