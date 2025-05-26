/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:34:50 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/25 23:56:07 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_utils_no(char **args, char **env, char ***sorted_env)
{
	if (!args || !env)
		return (1);
	sort_env(&env, sorted_env);
	return (0);
}

int	if_no_args(char **args, char **env, int i)
{
	char	**var_array;
	char	**sorted_env;

	if (ft_utils_no(args, env, &sorted_env))
		return (1);
	while (sorted_env[i])
	{
		if (ft_strchr(sorted_env[i], '='))
		{
			do_split_var(&var_array, sorted_env[i]);
			if (var_array[0][0] == '_')
			{
				i++;
				free_array(var_array);
				continue ;
			}
			printf("declare -x %s=\"%s\"\n", var_array[0], var_array[1]);
			free_array(var_array);
		}
		else
			printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	free_array(sorted_env);
	return (0);
}

void	msg_error(char *msg1, char *full, char *msg2)
{
	write(2, msg1, ft_strlen(msg1));
	write(2, full, ft_strlen(full));
	write(2, msg2, ft_strlen(msg2));
}

int	export_args(t_config *config, char *arg, char *name)
{
	char	*value;
	char	*full;
	int		equal_sign;
	char	*tmp;

	(void)config;
	full = ft_strdup(arg);
	equal_sign = split_var(arg, &name, &value);
	if (equal_sign)
	{
		if (valid_var_name(name, full))
			return (free(full), free(arg), 1);
		tmp = ft_strdup(value);
		ft_setenv(config, name, tmp);
	}
	if (!equal_sign && !valid_var_name(arg, full))
		ft_setenv(config, arg, NULL);
	else if (!equal_sign)
		return (free(full), free(arg), 1);
	free(arg);
	free(full);
	return (0);
}

int	ft_export(t_config *config, char **args)
{
	char	**env;
	char	*name;
	int		flag;
	int		i;

	name = NULL;
	flag = 0;
	env = config->env;
	if (!args[1])
		return (if_no_args(args, env, 0));
	i = 1;
	while (args[i])
	{
		if (export_args(config, ft_strdup(args[i]), name) == 1)
			flag = 1;
		i++;
	}
	exit_status(flag, 1);
	return (exit_status(flag, 0));
}
