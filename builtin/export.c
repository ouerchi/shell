/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:34:50 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/24 17:30:15 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_env_2(char **sorted_env, int count)
{
	int	i;
	int	j;
	char	*tmp;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(sorted_env[i], sorted_env[j]) > 0)
			{
				tmp = sorted_env[i];
				sorted_env[i] = sorted_env[j];
				sorted_env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	sort_env(char ***env, char ***sorted_env)
{
	int count;
	int	i;

	*sorted_env = NULL;
	count = 0;
	while ((*env)[count])
		count++;
	*sorted_env = (char **)malloc(sizeof(char *) * (count + 1));
	if (!(*sorted_env))
		return ;
	i = 0;
	while (i < count)
	{
		(*sorted_env)[i] = ft_strdup((*env)[i]);
		i++;
	}
	(*sorted_env)[count] = NULL;
	sort_env_2(*sorted_env, count);
}

void	do_split_var(char ***var_array, char *env)
{
	*var_array = NULL;
	*var_array = ft_split_var(env);
	if (!(*var_array)[1])
		(*var_array)[1] = ft_strdup("");
}

int	if_no_args(char **args, char **env)
{
	int	i;
	char	**var_array;
	char	**sorted_env;

	if (!args || !env)
		return (1);
	sort_env(&env, &sorted_env);
	i = 0;
	while (sorted_env[i])
	{
		if (ft_strchr(sorted_env[i], '='))
		{
			do_split_var(&var_array, sorted_env[i]);
			if (var_array[0][0] == '_')
			{
				i++;
				free_array(var_array);
				continue;
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
	int		flag;
	int		i;

	name = NULL;
	flag = 0;
	env = config->env;
	if (!args[1])
		return (if_no_args(args, env));
	i = 1;
	while (args[i])
	{
		if (export_args(config, ft_strdup(args[i]), name) == 1)
			flag = 1;
			// return (1);
		i++;
	}
	exit_status(flag, 1);
	return (exit_status(flag, 0));
}
