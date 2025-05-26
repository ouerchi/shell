/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 03:10:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/26 19:00:33 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_files(t_parse **p, t_files *new)
{
	t_files	*tmp;

	if (!new)
		return ;
	if (!*p)
	{
		*p = malloc(sizeof(t_parse));
		if (!(*p))
			return ;
		(*p)->file = new;
		(*p)->file->next = NULL;
		return ;
	}
	if (!(*p)->file)
	{
		(*p)->file = new;
		return ;
	}
	tmp = (*p)->file;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	check_option(char **args)
{
	if (!args[1])
		return (0);
	if (args[1][0] != '-')
		return (0);
	if (!args[1][1])
		return (0);
	return (1);
}

void	option_error(char *cmd, char *option)
{
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, option, ft_strlen(option));
	write(2, ": invalid option\n", 18);
}

void	env_error_arg(char *cmd, char *arg)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, "'", 1);
	write(2, arg, ft_strlen(arg));
	write(2, "': No such file or directory\n", 30);
}
