/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:07:25 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/23 23:38:56 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free_token_list(t_token *lst)
{
    t_token *tmp;

    while (lst)
    {
        tmp = lst;
        lst = lst->next;
        free(tmp->value);
        free(tmp->exp);
        free(tmp);
    }
}

void free_parse(t_parse *cmd)
{
    t_parse *tmp;
    int i;

    while (cmd)
    {
        tmp = cmd;
        cmd = cmd->next;
        free(tmp->cmd_name);
        if (tmp->args)
        {
            for (i = 0; tmp->args[i]; ++i)
                free(tmp->args[i]);
            free(tmp->args);
        }
        free(tmp);
    }
}

// void    free_herdoc(t_name **name)
// {
//     t_name  *tmp;

//     while (*name)
//     {
//         tmp = (*name)->next;
//         free(*name);
//         *name = tmp;
//     } 
//     free(name);
//     name = NULL;  
// }