/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:35:50 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/23 13:45:20 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_files_utils(t_name **her_name, t_parse *cmd, t_files *file)
{
	while (file)
	{
		if (file->name && f_strcmp(file->type, "REDIR_IN") == 0)
		{
			if (redir_in(cmd, file->name) == -1)
				return (-1);
		}
		else if (file->name && f_strcmp(file->type, "REDIR_OUT") == 0)
		{
			if (redir_out(cmd, file->name) == -1)
				return (-1);
		}
		else if (file->name && f_strcmp(file->type, "APPEND") == 0)
		{
			if (redir_append(cmd, file->name) == -1)
				return (-1);
		}
		else if (*her_name && f_strcmp(file->type, "HERDOC") == 0)
		{
			handel_her(cmd, (*her_name)->name);
			*her_name = (*her_name)->next;
		}
		file = file->next;
	}
	return (0);
}

int	open_files(t_name *her_name, t_parse *head_cmd)
{
	t_parse	*cmd;
	t_files	*file;

	cmd = head_cmd;
	while (cmd)
	{
		cmd->infile = -1;
		cmd->outfile = -1;
		file = cmd->file;
		if (open_files_utils(&her_name, cmd, file) == -1)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}
