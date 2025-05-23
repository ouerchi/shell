/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:30:37 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/23 23:42:59 by mouerchi         ###   ########.fr       */
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
		return(exit_status(127, 0), error_handling(1, cmd, ": No such file or directory", 127), 1);
	if (access(cmd, X_OK) != 0)
		return(exit_status(127, 0), error_handling(1, cmd, ": Permission denied", 126), 1);
	config->path = ft_strdup(cmd);
	return (0);
}

void	get_path(t_config *config, t_parse *cmd)
{
	if (is_path(cmd->cmd_name))
	{
		if (!ft_strncmp(cmd->cmd_name, ".", ft_strlen(cmd->cmd_name)))
			return ;
		if (is_directory(cmd->cmd_name) && f_strcmp(cmd->cmd_name, ".."))
			return (exit_status(126, 0), error_handling(1, cmd->cmd_name, ": Is a directory", 126));
		if (ft_strncmp(cmd->cmd_name, "...", ft_strlen("...")) && !check_cmd(config, cmd->cmd_name))
			return ;
	}
	config->path = find_path(cmd->cmd_name, config->env);
	if (config->path)
		return ;
	if (is_file(cmd->cmd_name) && !check_cmd(config, cmd->cmd_name))
		return ;
	if (is_directory(cmd->cmd_name))
		return (error_handling(1, cmd->cmd_name, ": Is a directory", 126));
	if (!check_cmd(config, cmd->cmd_name))
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
		// exit_status(127, 0);
	}
	exit(127);
}

// int	ft_split_path(char ***split_path, char **path, char **tmp, int *i)
// {
// 	*split_path = NULL;
// 	*tmp = NULL;
// 	*i = 0;
// }

// char	*ft_find_path(char *cmd, char *path)
// {
// 	char	**split_path;

// 	if (!cmd || !cmd_path)
// 		return (NULL);
// 	if (!ft_strlen(cmd) || ft_strchr("./", cmd[0]))
// 		return (ft_strdup(cmd));
// 	if (!ft_split_path(&split_path, &path, &tmp, &i))	
// }

// char	*get_cmd_path(t_config *config, char *cmd)
// {
// 	char	*cmd_path;

// 	cmd_path = ft_getenv(config->env, "PATH");
// 	if (!cmd_path)
// 		return (ft_strdup(cmd));
// 	else
// 		cmd_path = ft_find_path(cmd, cmd_path);
// }

// void	execute_cmd(t_config *config, t_parse *cmd)
// {
// 	char *cmd_path;
// 	char	**args;
	
// 	args = cmd->args;
// 	cmd_path = get_cmd_path(config, args[0]);
// }