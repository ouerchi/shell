/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:59:02 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/21 17:52:31 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *env_lst)
{
	t_env	*tmp;

	if (!env_lst)
		return (1);
	tmp = env_lst;
	while (tmp)
	{
		if (ft_strchr(tmp->variable, '='))
			printf("%s\n", tmp->variable);
		tmp = tmp->next;
	}
	return (0);
}
