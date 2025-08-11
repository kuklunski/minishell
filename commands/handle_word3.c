/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 03:03:35 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 03:03:35 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_new_tokens(t_token **tok)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = *tok;
	while (temp->type == WORD || temp->type == VAR)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

static int	count_existing_args(char **args)
{
	int	len;

	len = 0;
	while (args[len])
		len++;
	return (len);
}

void	copy_existing_args(char **new_tab, char **args, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new_tab[i] = args[i];
		i++;
	}
}

// old args= "command args1 args2" + new tokens "args3 args4"
// new_tab = "command args1 args2 args3 args4";
char	**copy_to_new_tab(int len, char **new_tab, t_command *l_cmd,
		t_token **tk_node)
{
	int		i;
	t_token	*temp;

	copy_existing_args(new_tab, l_cmd->args, len);
	i = len;
	temp = *tk_node;
	while (temp->type == WORD || temp->type == VAR)
	{
		new_tab[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

// copies the content of the tokens created to the command->args
// if they already exist.
// it counts the number of token of type WORD or VAR
// to add them as args to the command->args
// it counts the number of args in the command->args
// and allocates a new array of size (len + i + 1)
int	add_args_def(t_token **tok, t_command *l_cmd)
{
	int new_tokens;
	int old_args;
	char **new_tab;
	t_token *temp;

	new_tokens = count_new_tokens(tok);
	old_args = count_existing_args(l_cmd->args);
	new_tab = malloc(sizeof(char *) * (new_tokens + old_args + 1));
	if (!new_tab)
		return (FAILURE);
	new_tab = copy_to_new_tab(old_args, new_tab, l_cmd, tok);
	temp = *tok;
	while (temp->type == WORD || temp->type == VAR)
		temp = temp->next;
	free_str_tab(l_cmd->args);
	l_cmd->args = new_tab;
	*tok = temp;
	return (SUCCESS);
}