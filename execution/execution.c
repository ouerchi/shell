/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:05:13 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/24 20:32:36 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_io(t_config *config, t_parse *cmd)
{
	if (cmd->next)
	{
		ft_close(config->pipe[0]);
		if (dup2(config->pipe[1], STDOUT_FILENO) == -1)
			perror("dup2");
		ft_close(config->pipe[1]);
	}
	if (config->saved_fd != -1)
	{
		if (dup2(config->saved_fd, STDIN_FILENO) == -1)
			perror("dup2");
		ft_close(config->saved_fd);
	}
	if (cmd->infile != -1 && cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			perror("dup2");
		ft_close(cmd->infile);
	}
	if (cmd->outfile != -1 && cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			perror("dup2");
		ft_close(cmd->outfile);
	}
}

void	run_child_process(t_config *config, t_parse *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd->cmd_name)
		exit(0);
	redirect_io(config, cmd);
	if (cmd->file_fail)
		exit(1);
	if (cmd->builtins == 1)
	{
		config->child_flag = 1;
		exit_status(run_builtins(config, cmd), 0);
		exit(exit_status(1, 1));
	}
	execute_cmd(config, cmd);
}


int	run_single_cmd(t_config *config)
{
	int		status;
	t_parse	*cmd;

	cmd = config->cmd;
	if (!cmd->cmd_name)
		return (0);
	if (cmd->builtins)
	{
		config->child_flag = 0;
		config->std_in = dup(STDIN_FILENO);
		config->std_out = dup(STDOUT_FILENO);
		apply_redir(cmd);
		status = run_builtins(config, cmd);
		restore_redir(config);
		return (exit_status(status, 0), status);
	}
	status = spawn_child_process(config, cmd);
	parent(config);
	return (status);
}

int	exit_status(int status, int flag)
{
	static int	exit_status;

	if (flag != 1)
		exit_status = status;
	return (exit_status);
}

void	parent(t_config *config)
{
	int	status;
	t_pid	*pid;

	pid = config->pids;
	while (pid)
	{
		if (waitpid(pid->pid, &status, 0) == -1)
			perror(strerror(errno));
		else
		{
			if (WIFEXITED(status))
				exit_status(WEXITSTATUS(status), 0);
		}	
		pid = pid->next;
	}
	free_pids(&config->pids);
}

int	execution(t_config *config)
{
	int		cmd_nmbr;
	t_parse	*current_cmd;

	init_process(config);
	cmd_nmbr = ft_cmd_nmbr(config->cmd);
	open_files(config->her_name, config->cmd);
	if (cmd_nmbr == 1 && !config->cmd->file_fail)
		return (run_single_cmd(config));
	current_cmd = config->cmd;
	while (current_cmd && config->cmd_idx < cmd_nmbr)
	{
		spawn_child_process(config, current_cmd);
		current_cmd = current_cmd->next;
		config->cmd_idx++;
	}
	parent(config);
	return (0);
}
