/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:07:25 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/24 17:14:50 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free_token_list(t_token *lst)
{
    t_token *tmp;
    
    if (!lst)
        return ;
    while (lst)
    {
        tmp = lst;
        lst = lst->next;
        free(tmp->value);
        free(tmp->exp);
        free(tmp);
    }
}

// void    free_parse(t_parse **cmd)
// {
//     t_parse *tmp;

//     if (!cmd || !(*cmd))
//         return ;

//     while (cmd)
//     {
//         tmp = (*cmd)->next;
//         free((*cmd)->cmd_name);
//         free_array((*cmd)->args);
//         free(*cmd);
//         *cmd = tmp;
//     }
// }

void free_parse(t_parse **cmd)
{
	t_parse *current;
	t_parse *next;

	if (!cmd || !*cmd)
		return;
	
	current = *cmd;
	while (current)
	{
		next = current->next;
		if (current->cmd_name)
			free(current->cmd_name);
		if (current->args)
			free_array(current->args);
		// if (current->file)
		// 	free_files(current->file);
		free(current);

		current = next;
	}
	*cmd = NULL;
}