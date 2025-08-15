/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 03:59:06 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/13 23:29:05 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	skip_joined_vars(t_token **temp)
{
	while ((*temp)->type == VAR && (*temp)->join == true)
		*temp = (*temp)->next;
}

static bool	should_join_next_var(t_token *temp)
{
	if (!temp->next)
		return (false);
	if (temp->type != VAR)
		return (false);
	if (temp->next->type != VAR)
		return (false);
	if (temp->next->join != true)
		return (false);
	return (true);
}

static bool	is_var_with_join(t_token *temp)
{
	if (temp->type == VAR && temp->join == true)
		return (true);
	return (false);
}

char	*join_vars(t_token **token_node)
{
	t_token	*temp;
	char	*str;
	char	*tmp;

	temp = *token_node;
	str = ft_strdup(temp->str);
	while (should_join_next_var(temp))
	{
		tmp = ft_strjoin(str, temp->next->str);
		free_ptr(str);
		str = tmp;
		temp = temp->next;
	}
	*token_node = temp;
	return (str);
}

// we skip joined vars cause we count them as one arg
int	count_arguments(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD || temp->type == VAR))
	{
		if (is_var_with_join(temp))
		{
			skip_joined_vars(&temp);
			i++;
		}
		else
		{
			i++;
			temp = temp->next;
		}
	}
	return (i);
}
