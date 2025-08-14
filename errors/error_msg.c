/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:37:23 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/13 23:29:54 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// returns "base+addition"
char	*append_str(char *base, char *addition)
{
	char	*new_str;

	if (!addition)
		return (base);
	if (!base)
		return (ft_strdup(addition));
	new_str = ft_strjoin(base, addition);
	free_ptr(base);
	return (new_str);
}

int	error_cmd(char *command, char *detail, char *error_message, int error_nb)
{
	char	*msg;
	char	*prefix;
	char	*suffix;

	msg = ft_strdup("minishell: ");
	if (command != NULL)
	{
		msg = append_str(msg, command);
		msg = append_str(msg, ": ");
	}
	msg = append_str(msg, error_message);
	if (detail != NULL)
	{
		prefix = " `";
		suffix = "'";
		msg = append_str(msg, prefix);
		msg = append_str(msg, detail);
		msg = append_str(msg, suffix);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
	return (error_nb);
}

// final input would be like:
// minishell: error_message: detail
// example :// minishell: syntax error: unexpected end of file (if quotes)
// else
// example :// minishell: unexpected EOF while looking for matching `"'
void	error_msg(char *errmsg, char *detail, int quotes)
{
	char	*msg;
	char	*prefix;
	char	*suffix;

	msg = ft_strdup("minishell: ");
	msg = append_str(msg, errmsg);
	if (quotes)
	{
		prefix = " `";
		suffix = "'";
	}
	else
	{
		prefix = ": ";
		suffix = "";
	}
	msg = append_str(msg, prefix);
	msg = append_str(msg, detail);
	msg = append_str(msg, suffix);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
}
