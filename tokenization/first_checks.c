/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:10:46 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 22:58:18 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// expand, handle/remove quotes, then create commands
void	third_step(t_data *data)
{
	expansion(data, &data->token);
	parse_quotes(data);
	create_commands(data);
}

// second we tokenize and check for errors in consecutive redirs
// and at the same time add type = var to tokens that have vars
bool	second_step(t_data *data)
{
	if (tokenizer(data) == FAILURE)
		return (false);
	if (data->token->type == END)
		return (false);
	if (var_or_consecutive(&data->token) == FAILURE)
		return (false);
	return (true);
}

static bool	check_whitespace_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
				|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
			return (false);
		i++;
	}
	return (true);
}

bool	is_all_space(char *str)
{
	return (check_whitespace_only(str));
}

// first we check if no input and if input is only spaces
int	first_step(t_data *data)
{
	if (data->user_input == NULL)
		exit(0); // TODO: replace with proper exit_builtin when implemented
	else if (ft_strcmp(data->user_input, "\0") == 0)
		return (0);
	else if (check_whitespace_only(data->user_input))
		return (2);
	return (1);
}