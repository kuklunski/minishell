/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 04:06:14 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 22:58:14 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_existing_args(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

static char	**copy_echo_to_new_tab(int len, char **new_tab, t_command *l_cmd,
		t_token **tk_node)
{
	int		i;
	t_token	*temp;

	copy_existing_args(new_tab, l_cmd->args, len);
	i = len;
	temp = *tk_node;
	while (temp->type == WORD || temp->type == VAR)
	{
		if (temp->join == true)
			new_tab[i] = join_vars(&temp);
		else
		{
			new_tab[i] = ft_strdup(temp->str);
			temp = temp->next;
		}
		i++;
	}
	new_tab[i] = NULL;
	*tk_node = temp;
	return (new_tab);
}

// same as create_args_echo, except we add existing args
int	add_args_echo(t_token **tok, t_command *cmd)
{
	int new_args;
	int args;
	char **new_tab;

	remove_empty_args(tok);
	new_args = count_arguments(*tok);
	args = count_existing_args(cmd->args);
	new_tab = malloc(sizeof(char *) * (new_args + args + 1));
	if (!new_tab)
		return (FAILURE);
	new_tab = copy_echo_to_new_tab(args, new_tab, cmd, tok);
	free_ptr(cmd->args);
	cmd->args = new_tab;
	return (SUCCESS);
}