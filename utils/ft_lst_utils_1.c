/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 01:18:57 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/27 22:39:28 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_token_new(t_token_type type, void *content, void *content_2)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	if (content)
		new->value = ft_strdup(content);
	else
		new->value = NULL;
	if (content_2)
		new->exp = ft_strdup(content_2);
	else
		new->exp = NULL;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_files	*ft_files_new(char *name, char *type)
{
	t_files	*file;

	file = (t_files *)malloc(sizeof(t_files));
	if (!file)
		return (NULL);
	file->name = ft_strdup(name);
	file->type = ft_strdup(type);
	file->next = NULL;
	return (file);
}

t_parse	*ft_parse_new(void)
{
	t_parse	*new;

	new = (t_parse *)malloc(sizeof(t_parse));
	if (!new)
		return (NULL);
	new->cmd_name = NULL;
	new->args = NULL;
	new->file = NULL;
	new->builtins = 0;
	new->next = NULL;
	return (new);
}

t_token	*ft_lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
