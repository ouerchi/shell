/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_building_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:22:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/25 21:44:25 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fail_check(char ***env, int i)
{
	int	j;

	if (!(*env)[i])
	{
		j = 0;
		while (j < i)
			free((*env)[j++]);
		free(*env);
		return (0);
	}
	return (1);
}

char	*ft_getenv(char **env, char *env_name)
{
	int	i;
	int	env_len;

	if (!env || !(*env))
		return (NULL);
	i = 0;
	env_len = ft_strlen(env_name);
	while (env[i])
	{
		if (strncmp(env[i], env_name, env_len) == 0
			&& env[i][env_len] == '=')
			return (env[i] + env_len + 1);
		i++;
	}
	return (NULL);
}

char	**ft_split_var(char *variable)
{
	char	**splited_var;
	int		i;

	if (!variable)
		return (NULL);
	splited_var = (char **)malloc(sizeof(char *) * 3);
	if (!splited_var)
		return (NULL);
	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	if (!variable[i])
		return (free(splited_var), NULL);
	splited_var[0] = ft_substr(variable, 0, i);
	if (!splited_var[0])
		return (free(splited_var), NULL);
	i++;
	if (!variable[i])
		splited_var[1] = ft_strdup("");
	else
		splited_var[1] = ft_substr(variable, i, ft_strlen(variable));
	if (!splited_var[1])
		return (free(splited_var[0]), free(splited_var), NULL);
	splited_var[2] = NULL;
	return (splited_var);
}

void	ft_update_pwd_fail(t_config *config, char *arg)
{
	char	*old_pwd;
	char	*tmp;
	char	*updated_pwd;

	old_pwd = ft_getenv(config->env, "PWD");
	if (old_pwd)
	{
		write(2, "cd: error retrieving current directory: getcwd: cannot access \
parent directories: No such file or directory\n", 108);
		tmp = ft_strdup(old_pwd);
		updated_pwd = ft_strjoin(tmp, "/");
		updated_pwd = ft_strjoin(updated_pwd, arg);
		ft_setenv(config, "PWD", updated_pwd);
		ft_setenv(config, "OLDPWD", ft_strdup(old_pwd));
		update_env_array(config);
	}
	else
		return ;
}
