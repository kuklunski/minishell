/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 23:51:15 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/07 23:51:15 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char *res;
	int i = 0;
	int j = 0;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";

	res = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);

	while (s1[i])
		res[j++] = s1[i++];

	i = 0;
	while (s2[i])
		res[j++] = s2[i++];

	res[j] = '\0';
	return (res);
}