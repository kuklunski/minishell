/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:03:57 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/15 22:33:31 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Helper function to expand variables in a single word
static char	*expand_word_if_needed(t_data *data, char *word)
{
	if (ft_strchr(word, '$'))
	{
		word = expansion_heredoc(data, word);
		if (!word)
			return (NULL);
	}
	return (word);
}

// Helper function to process all words in split array
static bool	process_split_words(t_data *data, char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
	{
		split_line[i] = expand_word_if_needed(data, split_line[i]);
		if (!split_line[i])
			return (false);
		i++;
	}
	return (true);
}

// we split the line by spaces, then we expand each part
// to handle empty vars, empty vars will be replaced by an empty string
// and then skipped during the join
char *split_expand_join(t_data *data, char *line)
{
    char **split_line;
    char *result;

    split_line = ft_split(line, ' ');
    if (!split_line)
        return (NULL);

    if (!process_split_words(data, split_line))
    {
        free_str_tab(split_line);
        return (NULL);
    }

    result = join_back(split_line);
    free_str_tab(split_line);
    return (result);
}

// Helper function to check if line matches delimiter
// if yes, set ret to true as a flag that no error occured
// and return false to stop the loop
bool	is_delimiter_match(char *line, t_io_fds *io, bool *ret)
{
	if (ft_strcmp(line, io->heredoc_delimiter) == 0)
	{
		*ret = true;
		return (false);
	}
	return (true);
}

// Helper function to handle variable expansion
// if $ is found, we expand the variable
bool handle_var_expansion(t_data *data, char **line, t_io_fds *io, bool *ret)
{
    char *new_line;

    if (io->heredoc_quotes == false && ft_strchr(*line, '$'))
    {
        new_line = split_expand_join(data, *line);
        if (!new_line)
        {
            free(*line);
            *line = NULL;
            *ret = false;
            return (false);
        }
        free(*line);
        *line = new_line;
    }
    return (true);
}
