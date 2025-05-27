/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:30:37 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/27 19:45:28 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_handling(int flag, char *cmd, char *msg, int i)
{
	if (flag == 1)
		write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(i);
}

int	err_1(int f, char *c, char *m, int i)
{
	if (f == 1)
		write(2, "minishell: ", 11);
	write(2, c, ft_strlen(c));
	write(2, m, ft_strlen(m));
	write(2, "\n", 1);
	exit_status(1, 0);
	return (i);
}

int	check_cmd(t_config *config, char *cmd)
{
	(void)config;
	if (access(cmd, F_OK) != 0)
		return (exit_status(127, 0),
			error_handling(1, cmd, ": No such file or directory", 127), 1);
	if (access(cmd, X_OK) != 0)
		return (exit_status(127, 0),
			error_handling(1, cmd, ": Permission denied", 126), 1);
	return (0);
}

void	get_path(t_config *config, t_parse *cmd)
{
	if (ft_strlen(cmd->cmd_name) == 1 && cmd->cmd_name[0] == '.')
		return (exit_status(2, 0),
			error_handling(1, cmd->cmd_name, \
				": filename argument required", 2));
	if (ft_strchr(cmd->cmd_name, '/'))
	{
		if (is_directory(cmd->cmd_name))
			return (exit_status(126, 0),
				error_handling(1, cmd->cmd_name, ": Is a directory", 126));
	}
	if (ft_strlen(cmd->cmd_name) && cmd->cmd_name[0] == '.')
	{
		if (!check_cmd(config, cmd->cmd_name))
			execve(cmd->cmd_name, cmd->args, config->env);
		exit_status(0, 0);
		exit(exit_status(-1, 1));
	}
	config->path = find_path(cmd->cmd_name, config->env);
	if (config->path)
		return ;
	if (!check_cmd(config, cmd->cmd_name))
	{
		config->path = ft_strdup(cmd->cmd_name);
		return ;
	}
}

void	execute_cmd(t_config *config, t_parse *cmd)
{
	get_path(config, cmd);
	execve(config->path, cmd->args, config->env);
	error_handling(1, cmd->cmd_name, ": command not found", 2);
	if (config->path)
		free(config->path);
	exit_status(127, 0);
	exit(127);
}
