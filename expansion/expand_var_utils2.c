/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 03:05:08 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/13 23:47:11 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Copies a variable value into the new string at the current position
 * Example: if var_value = "john" and *j = 5
 * Copies "john" to new_str starting at position 5
 * Updates *j from 5 to 9 (after copying 4 characters)
 */
void	copy_var_value(char *new_str, char *var_value, int *j)
{
	int	k;

	if (!var_value)
		return ;
	k = 0;
	while (var_value[k])
	{
		new_str[*j] = var_value[k];
		k++;
		(*j)++;
	}
}

/*
 * Skips over a variable in the original string by advancing the index
 * Example: oldstr = "echo $USER hello", index = 5, var_end returns 4
 * *i starts at 5 (position of $), gets updated to 5 + 4 + 1 = 10
 * Now *i points to the space after "USER"
 */
static void	skip_variable(int *i, char *oldstr, int index)
{
	*i = *i + var_end(oldstr + index) + 1;
}

/*

	* Processes one character: either copies 
	a variable value or a regular character
 * Example: oldstr = "echo $USER", var_value = "john", index = 5
 * - If *i = 5 (at $): copies "john" to new_str, skips to after "USER"
 * - If *i = 0 (at 'e'): copies 'e' to new_str, advances both indices
 * Returns 1 if reached end of string, 0 to continue processing
 */
static int	process_char_or_var(t_proc_ctx *ctx)
{
	if (ctx->oldstr[*(ctx->i)] == '$' && *(ctx->i) == ctx->index)
	{
		copy_var_value(ctx->new_str, ctx->var_value, ctx->j);
		skip_variable(ctx->i, ctx->oldstr, ctx->index);
		if (ctx->oldstr[*(ctx->i)] == '\0')
			return (1);
	}
	else
	{
		ctx->new_str[(*(ctx->j))++] = ctx->oldstr[(*(ctx->i))++];
	}
	return (0);
}

/*
 * Builds the complete new string by processing each character from the original
 * Example: oldstr = "echo $USER hello", var_value = "john", index = 5
 * Process: "echo " (copy chars 0-4) + "john" (replace $USER)
	+ " hello" (copy remaining)
 * Result in new_str: "echo john hello"
 * Handles loop control and null termination
 * ctx is just for norminette
 */
static void	build_new_string(char *new_str, char *oldstr, char *var_value,
		int index)
{
	int			i;
	int			j;
	t_proc_ctx	ctx;

	ctx.new_str = new_str;
	ctx.oldstr = oldstr;
	ctx.var_value = var_value;
	ctx.index = index;
	ctx.i = &i;
	ctx.j = &j;
	i = 0;
	j = 0;
	while (oldstr[i])
	{
		if (process_char_or_var(new_str, oldstr, var_value, &i, &j, index))
			break ;
	}
	new_str[j] = '\0';
}

/*
 * Creates a new token string with variable replacement
 * Example: oldstr = "echo $USER hello", var_value = "john", newstr_size = 16,
	index = 5
 * 1. Allocates 16 bytes for new string
 * 2. Calls build_new_string to fill it with "echo john hello"
 * 3. Returns pointer to the new string
 * Returns NULL if memory allocation fails
 */
char	*new_token_string(char *oldstr, char *var_value, int newstr_size,
		int index)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * newstr_size);
	if (!new_str)
		return (NULL);
	build_new_string(new_str, oldstr, var_value, index);
	return (new_str);
}
