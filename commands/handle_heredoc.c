/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 04:33:32 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 18:56:09 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_delim(bool *quotes, char *str)
{
	char	*delim;
	int		len;
	char	c;
	char	cc;

	len = ft_strlen(str);
	c = str[0];
	cc = str[len - 1];
	*quotes = false;
	if ((c == '\'' && cc == '\'') || (c == '"' && cc == '"'))
	{
		*quotes = true;
		delim = ft_substr(str, 1, len - 2);
	}
	else
		delim = ft_strdup(str);
	return (delim);
}

static char	*create_heredoc_name(void)
{
	static int	heredoc_count = 0;
	char		*heredoc_name;
	char		*i;

	heredoc_count++;
	i = ft_itoa(heredoc_count);
	heredoc_name = ft_strjoin("/tmp/mini_heredoc_", i);
	if (!heredoc_name)
		write(STDERR_FILENO, "Error creating heredoc name\n", 28);
	free(i);
	return (heredoc_name);
}

// Helper function to get last command and initialize I/O
static t_io_fds	*get_last_cmd_io(t_command **cmd)
{
	t_command	*tcmd;

	tcmd = *cmd;
	while (tcmd->next != NULL)
		tcmd = tcmd->next;
	init_inf_outf(tcmd);
	return (tcmd->io_fds);
}

// Helper function to advance token pointer
static void	advance_tokens(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	temp = temp->next;
	if (temp->next && temp->next->next)
		temp = temp->next->next;
	*tokens = temp;
}

void	handle_heredoc(t_command **cmd, t_token **tokens, t_data *data)
{
	t_token		*temp;
	t_io_fds	*i_o;
	int			heredoc_fd;
	bool		ret;

	temp = *tokens;
	i_o = get_last_cmd_io(cmd);
	if (!remove_old_infile(i_o))
		return ;
	i_o->infile = create_heredoc_name();
	i_o->heredoc_delimiter = find_delim(&(i_o->heredoc_quotes),
			temp->next->str);
	i_o->fd_in = -1;
	ret = true;
	heredoc_fd = open(i_o->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = write_to_heredoc(data, i_o, heredoc_fd);
	close(heredoc_fd);
	if (ret)
		i_o->fd_in = open(i_o->infile, O_RDONLY);
	advance_tokens(tokens);
}
