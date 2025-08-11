/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:42:00 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 21:42:00 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	calculate_total_length(char **tab)
{
	int	total_len;
	int	i;

	total_len = 0;
	i = 0;
	while (tab[i])
	{
		if (tab[i][0] != '\0')  // Skip empty strings
			total_len += ft_strlen(tab[i]) + 1;  // +1 for space
		i++;
	}
	if (total_len > 0)
		total_len--;  // Remove the last space
	return (total_len);
}

static void	copy_words_to_result(char *result, char **tab)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (tab[i])
	{
		if (tab[i][0] != '\0')  // Skip empty strings
		{
			if (j > 0)  // Add space before word (except first)
				result[j++] = ' ';
			k = 0;
			while (tab[i][k])
				result[j++] = tab[i][k++];
		}
		i++;
	}
	result[j] = '\0';
}

char	*join_back(char **tab)
{
	char	*result;
	int		total_len;

	if (!tab || !tab[0])
		return (ft_strdup(""));
	total_len = calculate_total_length(tab);
	if (total_len == 0)
		return (ft_strdup(""));
	result = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!result)
		return (NULL);
	copy_words_to_result(result, tab);
	return (result);
}
