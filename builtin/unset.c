/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:58:51 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/29 16:57:08 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_remove_env_node(t_env **head, char *var)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *head;
	prev = NULL;
	while (tmp)
	{
		if ((ft_strlen(var) == ft_strlen(tmp->name))
			&& !ft_strncmp(tmp->name, var, ft_strlen(var)))
		{
			if (!prev)
				*head = tmp->next;
			else
				prev->next = tmp->next;
			free_env_node(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_config *config, char **args)
{
	int		i;

	if (!args)
		return (1);
	if (!args[1])
		return (0);
	else
	{
		i = 1;
		while (args[i])
		{
			ft_remove_env_node(&config->env_lst, args[i]);
			i++;
		}
	}
	return (0);
}
