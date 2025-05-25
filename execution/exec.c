/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:30:37 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/25 20:27:42 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_handling(int flag, char *cmd, char *msg, int i)
{
	if (flag == 1)
		ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(i);
}

int	check_cmd(t_config *config, char *cmd)
{
	if (access(cmd, F_OK) != 0)
		return (exit_status(127, 0),
			error_handling(1, cmd, ": No such file or directory", 127), 1);
	if (access(cmd, X_OK) != 0)
		return (exit_status(127, 0),
			error_handling(1, cmd, ": Permission denied", 126), 1);
	config->path = ft_strdup(cmd);
	return (0);
}

void	get_path(t_config *config, t_parse *cmd)
{
	if (ft_strchr(cmd->cmd_name, '/'))
	{
		if (is_directory(cmd->cmd_name))
			return (exit_status(126, 0),
				error_handling(1, cmd->cmd_name, ": Is a directory", 126));
		check_cmd(config, cmd->cmd_name);
	}
	if (ft_strchr(cmd->cmd_name, '.') && !check_cmd(config, cmd->cmd_name))
		return ;
	config->path = find_path(cmd->cmd_name, config->env);
	if (config->path)
		return ;
	if (is_file(cmd->cmd_name) && !check_cmd(config, cmd->cmd_name))
		return ;
}

void	execute_cmd(t_config *config, t_parse *cmd)
{
	get_path(config, cmd);
	if (execve(config->path, cmd->args, config->env) == -1)
	{
		write(2, cmd->cmd_name, ft_strlen(cmd->cmd_name));
		write(2, ": command not found\n", ft_strlen(": command not found\n"));
		free(config->path);
		exit_status(127, 0);
	}
	exit(127);
}
