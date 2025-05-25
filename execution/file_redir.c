/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:22:52 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/25 20:22:22 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup(int fd, int redir)
{
	if (dup2(fd, redir) == -1)
		perror("dup2");
	return ;
}

void	ft_close(int fd)
{
	if (fd > 0)
	{
		if (close(fd) == -1)
			perror("close");
	}
	return ;
}

void	restore_redir(t_config *config)
{
	ft_dup(config->std_in, STDIN_FILENO);
	ft_dup(config->std_out, STDOUT_FILENO);
	ft_close(config->std_in);
	ft_close(config->std_out);
}

void	apply_redir(t_parse *cmd)
{
	if (cmd->outfile != -1)
	{
		ft_dup(cmd->outfile, STDOUT_FILENO);
		ft_close(cmd->outfile);
	}
	if (cmd->infile != -1)
	{
		ft_dup(cmd->infile, STDOUT_FILENO);
		ft_close(cmd->infile);
	}
}
