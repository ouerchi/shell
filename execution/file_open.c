/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:35:50 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/30 21:15:13 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handel_outfile(t_parse *cmd, char *file_name, char *file_type)
{
	if (file_name && f_strcmp(file_type, "REDIR_OUT") == 0)
	{
		if (redir_out(cmd, file_name) == -1)
			return (-1);
	}
	else if (file_name && f_strcmp(file_type, "APPEND") == 0)
	{
		if (redir_append(cmd, file_name) == -1)
			return (-1);
	}
	return (0);
}

int	open_files_utils(t_name **her_name, t_parse *cmd, t_files *file)
{
	t_name	*tmp;

	while (file)
	{
		if (file->name && f_strcmp(file->type, "REDIR_IN") == 0)
		{
			if (redir_in(cmd, file->name) == -1)
				return (-1);
		}
		else if (file->name && (!f_strcmp(file->type, "REDIR_OUT")
				|| !f_strcmp(file->type, "APPEND")))
		{
			if (handel_outfile(cmd, file->name, file->type) == -1)
				return (-1);
		}
		else if (*her_name && f_strcmp(file->type, "HERDOC") == 0)
		{
			tmp = (*her_name)->next;
			handel_her(cmd, (*her_name)->fd);
			free(*her_name);
			*her_name = tmp;
		}
		file = file->next;
	}
	return (0);
}

int	open_files(t_name **her_name, t_parse *head_cmd)
{
	t_parse	*cmd;
	t_files	*file;

	cmd = head_cmd;
	while (cmd)
	{
		cmd->file_fail = 0;
		cmd->infile = -1;
		cmd->outfile = -1;
		file = cmd->file;
		if (open_files_utils(her_name, cmd, file) == -1)
			cmd->file_fail = 1;
		free_files(file);
		cmd = cmd->next;
	}
	*her_name = NULL;
	return (0);
}

void	close_her(t_name *name)
{
	t_name	*tmp;

	if (!name)
		return ;
	while (name)
	{
		tmp = name->next;
		ft_close(name->fd);
		name = tmp;
	}
	name = NULL;
}

char	*handel_one_path(char **path, char *cmd_name)
{
	char	*tmp;
	char	*cmnd;

	tmp = NULL;
	cmnd = NULL;
	tmp = ft_strjoin_2(path[0], "/");
	cmnd = ft_strjoin(tmp, cmd_name);
	free(path[0]);
	free(path); 
	check_cmd(NULL, cmnd);
	return (cmnd);
}
