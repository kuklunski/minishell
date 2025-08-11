/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 04:21:01 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 04:21:01 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_str_tab(char **tab)
{
	int i = 0;

	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}