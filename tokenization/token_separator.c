/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:55:45 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/07 23:55:45 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	double_sep(t_token **lst, char *str, int i, int type)
{
	int		j;
	char	*sep;
	t_token	*new_node;

	j = 0;
	sep = malloc(sizeof(char) * 3);
	if (!sep)
		return (1);
	while (j < 2)
		sep[j++] = str[i++];
	sep[j] = '\0';
	new_node = create_token(sep, NULL, type, DEFAULT);
	add_token_to_list(lst, new_node);
	return (0);
}

static int	one_sep(t_token **lst, char *str, int i, int type)
{
	int		j;
	char	*sep;
	t_token	*new_node;

	j = 0;
	sep = malloc(sizeof(char) * 2);
	if (!sep)
		return (1);
	while (j < 1)
		sep[j++] = str[i++];
	sep[j] = '\0';
	new_node = create_token(sep, NULL, type, DEFAULT);
	add_token_to_list(lst, new_node);
	return (0);
}

int	token_separator(t_token **lst, char *str, int i, int type)
{
	if (type == APPEND || type == HEREDOC)
		return (double_sep(lst, str, i, type));
	else
		return (one_sep(lst, str, i, type));
}