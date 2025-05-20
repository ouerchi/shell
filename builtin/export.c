/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:34:50 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/20 23:08:34 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_no_args(char **args, char **env)
{
	int	i;
	char	**var_array;

	if (!args || !env)
		return (1);
	i = 0;
	while (env[i])
	{
		
		if (ft_strchr(env[i], '='))
		{
			var_array = ft_split(env[i], "=");
			if (!var_array[1])
				var_array[1] = ft_strdup("");
			printf("declare -x %s=\"%s\"\n", var_array[0], var_array[1]);
		}
		else
			printf("declare -x %s\n", env[i]);
		i++;
	}		
	return (0);
}

void	msg_error(char *msg1, char *full, char *msg2)
{
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(full, 2);
	ft_putstr_fd(msg2, 2);
}

int	export_args(t_config *config, char *arg, char *name)
{
	char	*value;
	char	*full;
	int		equal_sign;

	(void)config;
	full = ft_strdup(arg);
	equal_sign = split_var(arg, &name, &value);
	if (equal_sign)
	{
		if (valid_var_name(name, full))
			return (free(full), free(arg), 1);
		ft_setenv(config, name, ft_strdup(value));
	}
	if (!equal_sign && !valid_var_name(arg, full))
		ft_setenv(config, arg, NULL);
	else if (!equal_sign)
		return (free(full), 1);
	free(arg);
	free(full);
	return (0);
}

int	ft_export(t_config *config, char **args)
{
	char	**env;
	char	*name;
	int		i;

	name = NULL;
	env = config->env;
	if (!args[1])
		return (if_no_args(args, env));
	i = 1;
	while (args[i])
	{
		if (export_args(config, ft_strdup(args[i]), name))
			return (1);
		i++;
	}
	return (0);
}
