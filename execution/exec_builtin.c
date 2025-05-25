/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:29:51 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/25 20:17:32 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_cmd_name(char *name)
{
	if ((ft_strlen(name) == ft_strlen("exit"))
		&& (!ft_strncmp(name, "exit", ft_strlen(name))))
		return (1);
	else if ((ft_strlen(name) == ft_strlen("echo"))
		&& (!ft_strncmp(name, "echo", ft_strlen(name))))
		return (2);
	else if ((ft_strlen(name) == ft_strlen("export"))
		&& (!ft_strncmp(name, "export", ft_strlen(name))))
		return (3);
	else if ((ft_strlen(name) == ft_strlen("cd"))
		&& (!ft_strncmp(name, "cd", ft_strlen(name))))
		return (4);
	else if ((ft_strlen(name) == ft_strlen("env"))
		&& (!ft_strncmp(name, "env", ft_strlen(name))))
		return (5);
	else if ((ft_strlen(name) == ft_strlen("pwd"))
		&& (!ft_strncmp(name, "pwd", ft_strlen(name))))
		return (6);
	else if ((ft_strlen(name) == ft_strlen("unset"))
		&& (!ft_strncmp(name, "unset", ft_strlen(name))))
		return (7);
	return (0);
}

int	run_builtins(t_config *config, t_parse *cmd)
{
	char	*tmp;
	int		status;

	status = 0;
	tmp = NULL;
	if (check_cmd_name(cmd->cmd_name) == 1)
		status = ft_exit(cmd->args, config->child_flag);
	else if (check_cmd_name(cmd->cmd_name) == 2)
	{
		tmp = array_join(&cmd->args[1]);
		status = ft_echo(tmp);
		free(tmp);
	}
	else if (check_cmd_name(cmd->cmd_name) == 3)
	{
		if (check_option(cmd->args))
			return (option_error(cmd->cmd_name, cmd->args[1]), 2);
		status = ft_export(config, cmd->args);
		update_env_array(config);
	}
	else
		status = run_builtins_rest(config, cmd);
	return (status);
}

int	run_builtins_rest_2(t_config *config, t_parse *cmd)
{
	int			status;
	static int	cd_broken;
	char		*cwd;

	cwd = NULL;
	status = 0;
	if (check_cmd_name(cmd->cmd_name) == 5)
	{
		if (check_option(cmd->args))
			return (option_error(cmd->cmd_name, cmd->args[1]), 125);
		if (cmd->args[1])
			return (env_error_arg(cmd->cmd_name, cmd->args[1]), 127);
		status = ft_env(config->env_lst);
	}
	else if (check_cmd_name(cmd->cmd_name) == 4)
	{
		status = ft_cd(cmd->args[1], (config)->env, &cd_broken);
		cwd = getcwd(NULL, 0);
		if (status == -1 && !cwd)
			return (ft_update_pwd_fail(config, cmd->args[1]), 1);
		else
			ft_update_pwd(config);
	}
	return (free(cwd), status);
}

int	run_builtins_rest(t_config *config, t_parse *cmd)
{
	int		status;

	status = 0;
	if (check_cmd_name(cmd->cmd_name) == 7)
	{
		if (check_option(cmd->args))
			return (option_error(cmd->cmd_name, cmd->args[1]), 2);
		status = ft_unset(config, cmd->args);
		update_env_array(config);
	}
	else if (check_cmd_name(cmd->cmd_name) == 6)
	{
		if (check_option(cmd->args))
			return (option_error(cmd->cmd_name, cmd->args[1]), 2);
		status = ft_pwd(config);
	}
	else
		status = run_builtins_rest_2(config, cmd);
	return (status);
}
