/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:50:17 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/26 00:18:11 by mouerchi         ###   ########.fr       */
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

char	*ft_strjoin_2(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*dst;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dst = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strcpy_join(dst, s1, s2);
	return (dst);
}

int	empty_rl(char *rl)
{
	if (!ft_strlen(rl) || !ft_isspace(rl))
		return (free(rl), 0);
	return (1);
}
