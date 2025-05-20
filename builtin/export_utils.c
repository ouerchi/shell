/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:53:32 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/20 20:57:30 by mouerchi         ###   ########.fr       */
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
	int i;

	if (!name[0] || (!ft_isalpha(name[0])&& name[0] != '_'))
		return (msg_error("minishell: export: `", full, "' : not a valid identifier\n"), 1);
	i = 0;
	while (name[i] && name[i] != '+')
	{
		if (!is_valid_char(name[i]))
			return (msg_error("minishell: export: `", full, "' : not a valid identifier\n"), 1);
		i++;
	}
	if (name[i] == '+' && name[i + 1] != '\0')
		return (msg_error("minishell: export: `", full, "' : not a valid identifier\n"), 1);
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
