/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:51:25 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/13 23:32:24 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Calculates the new string length after removing a variable
 * Example: if token_str = "echo $USER hello" and index = 5 (position of $)
 * and var_end returns 4 (length of "USER"), then:
 * original_length = 16, var_length = 4
 * Returns: 16 - 4 = 12 (length of "echo  hello")
 */
static int	calculate_new_length(char *token_str, int index)
{
	int	original_length;
	int	var_length;

	original_length = ft_strlen(token_str);
	var_length = var_end(token_str + index);
	return (original_length - var_length);
}

/*
 * Copies characters from token_str to new_str, skipping the variable at index
 * Example: token_str = "echo $USER hello", index = 5
 * Copies: "echo " (chars 0-4), then skips "$USER" (chars 5-9),
 * then copies " hello" (chars 10-15)
 * Result in new_str: "echo  hello"
 */
static void	copy_without_var(char *new_str, char *token_str, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token_str[i])
	{
		if (token_str[i] == '$' && i == index)
		{
			i = i + var_end(token_str + index) + 1;
			if (token_str[i] == '\0')
				break ;
		}
		new_str[j++] = token_str[i++];
	}
	new_str[j] = '\0';
}

/*
 * Creates a new string without the variable at the specified index
 * Example: token_str = "echo $USER hello", index = 5
 * 1. Calculates new length (12 characters)
 * 2. Allocates memory for new string (13 bytes including null terminator)
 * 3. Copies content excluding the variable
 * Returns: pointer to "echo  hello" or NULL if allocation fails
 */
static char	*create_string_without_var(char *token_str, int index)
{
	char	*new_str;
	int		len;

	len = calculate_new_length(token_str, index);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (NULL);
	copy_without_var(new_str, token_str, index);
	return (new_str);
}

/*
 * Deletes a variable from a token by replacing the token's string
 * Example: token contains "echo $USER hello", i = 5
 * 1. Creates new string "echo  hello" (without $USER)
 * 2. Frees the old token string
 * 3. Assigns the new string to the token
 * Returns: 0 on success, 1 on memory allocation failure
 */
int	delete_var(t_token **token_node, char *token_str, int i)
{
	char	*new_str;

	new_str = create_string_without_var(token_str, i);
	if (!new_str)
		return (1);
	free_ptr((*token_node)->str);
	(*token_node)->str = new_str;
	return (0);
}
