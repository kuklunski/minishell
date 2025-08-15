/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 04:14:41 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 04:14:41 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_token_strings(t_token *lst)
{
	if (lst && lst->str)
	{
		free_ptr(lst->str);
		lst->str = NULL;
	}
	if (lst && lst->str_backup)
	{
		free_ptr(lst->str_backup);
		lst->str_backup = NULL;
	}
}

static void	unlink_token_from_list(t_token *lst)
{
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
}

void	delete_token(t_token *lst)
{
	free_token_strings(lst);
	unlink_token_from_list(lst);
	free_ptr(lst);
}
// clears the entire token list
void	clear_list_token(t_token **lst)
{
	t_token *tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		delete_token(*lst);
		*lst = tmp;
	}
}