/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:53:32 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/25 22:12:02 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_char(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (0);
	return (1);
}

int	valid_var_name(char *name, char *full)
{
	int	i;

	if (!name[0] || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (msg_error("minishell: export: `", full, "' : \
not a valid identifier\n"), exit_status(1, 0), 1);
	i = 0;
	while (name[i] && name[i] != '+')
	{
		if (!is_valid_char(name[i]))
			return (msg_error("minishell: export: `", full, "' : \
not a valid identifier\n"), exit_status(1, 0), 1);
		i++;
	}
	if (name[i] == '+' && name[i + 1] != '\0')
		return (msg_error("minishell: export: `", full, "' : \
not a valid identifier\n"), exit_status(1, 0), 1);
	return (0);
}

int	split_var(char *arg, char **name, char **value)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return (0);
	*equal = '\0';
	*name = arg;
	*value = equal + 1;
	return (1);
}

void	sort_env_2(char **sorted_env, int count)
{
	int		i;
	int		j;
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
	int	count;
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
