/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 02:51:03 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 22:24:44 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_args_from_split(char **split, t_token **new_tok)
{
	t_token	*new_node;
	int		i;

	i = 1;
	while (split[i])
	{
		new_node = create_token(ft_strdup(split[i]), NULL, WORD, DEFAULT);
		add_token_to_list(new_tok, new_node);
		i++;
	}
	new_node = create_token(NULL, NULL, END, DEFAULT);
	add_token_to_list(new_tok, new_node);
}

// splits the token->str
// puts split[0] as the first command example: echo "$home" -> split[0] = "echo"
void	split_token(t_command *last_cmd, char *cmd_str)
{
	t_token *new_tokens;
	t_token *tmp;
	char **splitted;

	new_tokens = NULL;
	splitted = ft_split(cmd_str, ' ');
	if (!splitted)
		return ;
	last_cmd->command = ft_strdup(splitted[0]);
	create_args_from_split(splitted, &new_tokens);
	tmp = new_tokens;
	fill_arguments(&new_tokens, last_cmd);
	clear_list_token(&tmp);
	free_str_tab(splitted);
}