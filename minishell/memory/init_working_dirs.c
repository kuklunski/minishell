/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_working_dirs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+
        +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+
        +#+        */
/*                                                +#+#+#+#+#+
        +#+           */
/*   Created: 2025/08/10 21:14:53 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/10 21:14:53 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
returns the value of an env var
*/
char    *env_var_value(char **env, char *var)
{
    int i;
    int var_len;

    i = 0;
    var_len = ft_strlen(var);
    if (!var || !*var || var_len <= 0 || !env)
        return (NULL);
    while (env[i])
    {
        if (ft_strncmp(var, env[i], var_len) == 0)
            return (env[i] + ft_strlen(var));
        i++;
    }
    return (NULL);
}

/*
checks if an env var exists
*/
bool    env_var_exists(char **env, char *var)
{
    int i;
    int var_len;

    i = 0;
    if (!env || !var || !*var)
        return (false);
    var_len = ft_strlen(var);
    if (var_len <= 0)
        return (false);
    while (env[i])
    {
        if (ft_strncmp(var, env[i], var_len) == 0)
            return (true);
        i++;
    }
    return (false);
}

bool    init_working_dirs(t_data *data)
{
    char buffer[4096];
    char *working_dir;

    working_dir = getcwd(buffer, 4096);
    if (!working_dir)
        return (false);
    data->working_dir = ft_strdup(working_dir);
    if (!data->working_dir)
        return (false);
    if (env_var_exists(data->env, "OLDPWD="))
        data->old_working_dir = ft_strdup(env_var_value(data->env, "OLDPWD="));
    else
        data->old_working_dir = ft_strdup(working_dir);
    if (!data->old_working_dir)
    {
        free(data->working_dir);
        data->working_dir = NULL;
        return (false);
    }
    return (true);
}