/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:26:19 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/30 19:48:21 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_name	*ft_name_new(int fd)
{
	t_name	*her_name;

	her_name = (t_name *)malloc(sizeof(t_name));
	if (!her_name)
		return (NULL);
	her_name->fd = fd;
	her_name->next = NULL;
	return (her_name);
}

void	ft_lstadd_back_name(t_name **name, t_name *new)
{
	t_name	*tmp;

	if (!name || !new)
		return ;
	if (!(*name))
	{
		*name = new;
		return ;
	}
	tmp = *name;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	*ft_gen_name_file(void)
{
	int		fd;
	int		num;
	char	*name;
	char	c_read;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (perror("failed to open"), NULL);
	num = 0;
	name = (char *)malloc(102);
	if (!name)
		return (close(fd), NULL);
	while (num < 101)
	{
		if (read(fd, &c_read, 1) < 0)
			return (close(fd), perror("failed to read\n"), NULL);
		if (ft_isalnum(c_read))
			name[num++] = c_read;
	}
	name[num] = '\0';
	close(fd);
	return (name);
}

void	ft_free_name_list(t_name *name)
{
	t_name	*tmp;

	if (!name)
		return ;
	while (name)
	{
		tmp = name->next;
		free(name);
		name = tmp;
	}
	name = NULL;
}

int	extra_her(t_token *token, t_her *her)
{
	her->val = validate_pipes_her(token, her);
	if (her->val == 1 && ft_find_her(token) > 16)
	{
		write(2, "minishell: maximum here-document count exceeded\n", 48);
		return (exit_status(2, 0), 0);
	}
	else if (her->val == 0 && her->count_per > 16)
	{
		write(2, "minishell: maximum here-document count exceeded\n", 48);
		return (exit_status(2, 0), 0);
	}
	return (1);
}
