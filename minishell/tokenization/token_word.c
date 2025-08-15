/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:35:42 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/07 23:35:42 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	copy_word(char *word, char *str, int start, int index)
{
	int	i;

	i = 0;
	while (start < index)
	{
		word[i] = str[start];
		start++;
		i++;
	}
	word[i] = '\0';
}

int	token_word(t_token **token_list, char *str, int index, int start)
{
	char *word;
	t_token *new_node;

	word = malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (1);
	copy_word(word, str, start, index);
	new_node = create_token(word, ft_strdup(word), WORD, DEFAULT);
	add_token_to_list(token_list, new_node);
	return (0);
}