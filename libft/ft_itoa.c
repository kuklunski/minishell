/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:51:37 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/07 23:51:37 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_size(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int num)
{
	char *dst;
	int count;
	int i;
	long int n = num;

	count = count_size(n);
	if (n < 0)
		count++; // For '-'

	dst = (char *)malloc((count + 1) * sizeof(char));
	if (!dst)
		return (NULL);

	dst[count] = '\0';
	i = count - 1;

	if (n < 0)
	{
		n = -n;
		dst[0] = '-';
	}

	while (n >= 10)
	{
		dst[i--] = (n % 10) + '0';
		n /= 10;
	}
	dst[i] = n + '0';

	return (dst);
}