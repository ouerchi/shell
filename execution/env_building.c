/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_building.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:38:47 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/28 19:49:10 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_env(t_config *config, char *tmp)
{
	size_t	shell_level;

	if (!ft_getenv(config->env, "PATH"))
		ft_setenv(config, "PATH", \
			ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
	if (!ft_getenv(config->env, "SHLVL"))
		ft_setenv(config, "SHLVL", ft_strdup("1"));
	else
	{
		tmp = ft_getenv(config->env, "SHLVL");
		shell_level = ft_atoi(tmp, false) + 1;
		update_shlvl(&shell_level);
		tmp = ft_itoa(shell_level);
		ft_setenv(config, "SHLVL", tmp);
	}
	if (!ft_getenv(config->env, "_"))
		ft_setenv(config, "_", ft_strdup("/usr/bin/env"));
	if (!ft_getenv(config->env, "PWD"))
	{
		tmp = NULL;
		tmp = getcwd(tmp, 0);
		ft_setenv(config, "PWD", ft_strdup(tmp));
		free(tmp);
	}
	update_env_array(config);
}

t_env	*get_env_lst(t_config *config)
{
	char	**env;
	int		i;
	t_env	*lst;

	if (config->env_lst)
		return (free_env_lst(config->env_lst), NULL);
	env = config->env;
	if (!env)
		return (NULL);
	lst = NULL;
	i = 0;
	while (env[i])
	{
		append_env_lst(&lst, env[i]);
		if (!lst)
			return (NULL);
		i++;
	}
	return (lst);
}

char	**get_env(char **real_env)
{
	char	**env;
	int		i;
	int		count;

	if (!real_env || !(*real_env))
		return (NULL);
	count = 0;
	while (real_env[count])
		count++;
	env = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		env[i] = ft_strdup(real_env[i]);
		if (!fail_check(&env, i))
			return (NULL);
		i++;
	}
	env[count] = NULL;
	return (env);
}

void	init_env(t_config *config, char **env)
{
	config->amb = 0;
	config->flag_c = 0;
	config->isexpanded = 0;
	config->cmd = NULL;
	config->her_name = NULL;
	config->env = get_env(env);
	config->env_lst = NULL;
	config->env_lst = get_env_lst(config);
	check_env(config, NULL);
}
