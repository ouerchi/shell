/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:50:17 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/24 20:24:02 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*pid_new(pid_t pid)
{
	t_pid	*pids;

	pids = (t_pid *)malloc(sizeof(t_pid));
	if (!pids)
		return (NULL);
	pids->pid = pid;
	pids->next = NULL;
	return (pids);
}

void	lst_add_back_pid(t_pid **head, pid_t pid)
{
	t_pid	*new;
	t_pid	*tmp;

	new = pid_new(pid);
	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_pids(t_pid **head)
{
	t_pid	*tmp;
	t_pid	*next;

	if (!head || !(*head))
		return ;
	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}