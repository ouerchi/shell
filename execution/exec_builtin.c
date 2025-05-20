/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:29:51 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/20 22:10:10 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option(char **args)
{
	if (!args[1])
		return (0);
	if (args[1][0] != '-')
		return (0);
	return (1);
}

int	check_cmd_name(char *name)
{
	if ((ft_strlen(name) == ft_strlen("exit")) && (!ft_strncmp(name, "exit", ft_strlen(name))))
		return (1);
	else if ((ft_strlen(name) == ft_strlen("echo")) && (!ft_strncmp(name, "echo", ft_strlen(name))))
		return (2);
	else if ((ft_strlen(name) == ft_strlen("export")) && (!ft_strncmp(name, "export", ft_strlen(name))))
		return (3);
	else if ((ft_strlen(name) == ft_strlen("cd")) && (!ft_strncmp(name, "unset", ft_strlen(name))))
		return (4);
	else if ((ft_strlen(name) == ft_strlen("env")) && (!ft_strncmp(name, "pwd", ft_strlen(name))))
		return (5);
	else if ((ft_strlen(name) == ft_strlen("pwd")) && (!ft_strncmp(name, "cd", ft_strlen(name))))
		return (6);
	else if ((ft_strlen(name) == ft_strlen("unset")) && (!ft_strncmp(name, "env", ft_strlen(name))))
		return (7);
	return (0);
}

int	run_builtins(t_config *config, t_parse *cmd)
{
	char	*tmp;
	int		status;

	if (check_cmd_name(cmd->cmd_name) == 1)
		status = ft_exit(cmd->args);
	else if (check_cmd_name(cmd->cmd_name) == 2)
	{
		tmp = array_join(&cmd->args[1]);
		status = ft_echo(tmp);
		free(tmp);
	}
	else if (check_cmd_name(cmd->cmd_name) == 3)
	{
		status = ft_export(config, cmd->args);
		update_env_array(config);
	}
	else
		status = run_builtins_rest(config, cmd);
	return (status);
}

int	run_builtins_rest(t_config *config, t_parse *cmd)
{
	int		status;
	// char	*cwd;

	// cwd = NULL;
	status = 0;
	if (check_cmd_name(cmd->cmd_name) == 7)
	{
		status = ft_unset(config, cmd->args);
		update_env_array(config);
	}
	else if (check_cmd_name(cmd->cmd_name) == 6)
	{
		if (check_option(cmd->args))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("invalid option\n", 2);
			return (2);
		}
		status = ft_pwd(config);
	}
	else if (check_cmd_name(cmd->cmd_name) == 5)
		status = ft_env(config->env_lst);
	else if (check_cmd_name(cmd->cmd_name) == 4)
	{
		status = ft_cd(cmd->args[1], (config)->env);
	}
	return (status);
}