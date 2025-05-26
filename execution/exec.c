/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:30:37 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/26 15:21:35 by mouerchi         ###   ########.fr       */
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
	config->path = NULL;
	if (ft_strchr(cmd->cmd_name, '/'))
	{
		if (is_directory(cmd->cmd_name))
			return (exit_status(126, 0),
				error_handling(1, cmd->cmd_name, ": Is a directory", 126));
		check_cmd(config, cmd->cmd_name);
	}
	if (ft_strchr(cmd->cmd_name, '.'))
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
		if (config->path)
			free(config->path);
		exit_status(127, 0);
	}
	exit(127);
}
