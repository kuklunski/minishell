/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:25:00 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 21:25:00 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_to_zero(void *ptr, size_t size)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)ptr;
	i = 0;
	while (i < size)
	{
		p[i] = 0;
		i++;
	}
}

void	check_arguments(t_data *data, int ac, char **av)
{
	(void)data;
	if (ac > 1)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, av[1], ft_strlen(av[1]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		exit(127);
	}
}
