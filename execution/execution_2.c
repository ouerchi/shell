/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:34:33 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/29 18:19:17 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handel_her(t_parse *cmd, int fd)
{
	safe_close(&cmd->infile);
	cmd->infile = dup(fd);
	if (cmd->infile == -1)
	{
		close(fd);
		perror("dup");
	}
	ft_close(fd);
	return (0);
}

void	safe_close(int	*fd)
{
	if ((*fd) >= 0)
	{
		ft_close(*fd);
		*fd = -1;
	}
}

int	redir_in(t_parse *cmd, char *file_name)
{
	safe_close(&cmd->infile);
	cmd->infile = open(file_name, O_RDONLY);
	if (cmd->infile == -1)
	{
		write(2, "minishell: ", 11);
		write(2, file_name, ft_strlen(file_name));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit_status(1, 0);
		return (-1);
	}
	return (0);
}

int	redir_out(t_parse *cmd, char *file_name)
{
	if (is_directory(file_name))
		return (exit_status(1, 0), \
			msg_error("minishell: ", file_name, ": Is a directory\n"), 1);
	safe_close(&cmd->outfile);
	cmd->outfile = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->outfile == -1)
	{
		write(2, "minishell: : ", 13);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit_status(1, 0);
		return (-1);
	}
	return (0);
}

int	redir_append(t_parse *cmd, char *file_name)
{
	if (is_directory(file_name))
		return (exit_status(1, 0), \
			msg_error("minishell: ", file_name, ": Is a directory"), 1);
	safe_close(&cmd->outfile);
	cmd->outfile = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->outfile == -1)
	{
		write(2, "minishell: : ", 13);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit_status(1, 0);
		return (-1);
	}
	return (0);
}
