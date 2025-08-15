/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:10:46 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/15 18:35:18 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// static const char *token_type_to_str(int type)
// {
//     switch (type)
//     {
//         case 1:  return "SPACES";
//         case 2:  return "WORD";
//         case 3:  return "VAR";
//         case 4:  return "PIPE";
//         case 5:  return "INPUT";
//         case 6:  return "TRUNC";
//         case 7:  return "HEREDOC";
//         case 8:  return "APPEND";
//         case 9:  return "END";
//         default: return "UNKNOWN";
//     }
// }

// static void print_tokens(const t_token *head)
// {
//     int i = 0;
//     while (head)
//     {
//         printf("Token %d:\n", i);
//         printf("  str         : \"%s\"\n", head->str ? head->str : "(null)");
//         printf("  str_backup  : \"%s\"\n", head->str_backup ? head->str_backup : "(null)");
//         printf("  type        : (%s)\n", token_type_to_str(head->type));
//         printf("----------------------------\n");
//         head = head->next;
//         i++;
//     }
// }

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
		exit_builtin(data, NULL);
	else if (ft_strcmp(data->user_input, "\0") == 0)
		return (0);
	else if (check_whitespace_only(data->user_input))
		return (2);
	return (1);
}