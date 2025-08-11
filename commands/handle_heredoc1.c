/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 23:00:23 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 23:00:24 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Helper function to handle EOF case
// cat << END
// > This is line 1
// > This is line 2
// > ^D    ← User pressed Ctrl+D instead of typing "END"
// print warning: "warning: here-document delimited by end-of-file:
// wanted 'END'" and stop reading more lines
bool	handle_eof_line(t_io_fds *io, bool *ret)
{
	error_cmd("warning", "here-document delimited by end-of-file: wanted",
		io->heredoc_delimiter, true);
	*ret = true;
	return (false);
}

bool	parse_heredoc_line(t_data *data, char **line, t_io_fds *io, bool *ret)
{
	if (*line == NULL)
		return (handle_eof_line(io, ret));
	if (!is_delimiter_match(*line, io, ret))
		return (false);
	if (!handle_var_expansion(data, line, io, ret))
		return (false);
	return (true);
}

// Helper function to read a line with proper signal handling
char	*read_heredoc_line(void)
{
	char	*line;

	// set_signals_interactive();
	line = readline(">");
	// set_signals_noninteractive();
	return (line);
}

// Helper function to process and write a line to heredoc
void	write_heredoc_line(char *line, int fd)
{
	if (line)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	free_ptr(line);
}

bool	write_to_heredoc(t_data *data, t_io_fds *io, int fd)
{
	char	*line;
	bool	ret;

	ret = false;
	line = NULL;
	while (1)
	{
		line = read_heredoc_line();
		if (!parse_heredoc_line(data, &line, io, &ret))
			break ;
		write_heredoc_line(line, fd);
	}
	free_ptr(line);
	return (ret);
}
