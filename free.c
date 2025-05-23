/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:07:25 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/22 23:39:37 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    free(lst);
}

void free_parse(t_parse *cmd)
{
    t_files *next_file;
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
        while (tmp->file)
        {
            next_file = tmp->file->next;
            free(tmp->file->name);
            free(tmp->file->type);
            free(tmp->file);
            tmp->file = next_file;
        }
        free(tmp);
    }
    free(cmd);
}
