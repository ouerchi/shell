/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:44:31 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/26 17:45:15 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_her(t_name **name)
{
	t_name	*tmp;
	t_name	*next;

	if (!name)
		return ;
	tmp = *name;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;		
	}
}
