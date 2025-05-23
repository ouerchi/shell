/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:34:07 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/22 22:16:26 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_nmbr(t_parse *cmd_lst)
{
	t_parse	*current;
	int		count_cmd;

	current = cmd_lst;
	count_cmd = 0;
	while (current)
	{
		count_cmd++;
		current = current->next;
	}
	return (count_cmd);
}

char	*array_join(char **str)
{
	char	*rtrn;
	int		i;

	i = 0;
	rtrn = ft_strdup("");
	while (str[i])
	{
		if (i > 0)
			rtrn = ft_strjoin(rtrn, " ");
		rtrn = ft_strjoin(rtrn, str[i]);
		i++;
	}
	return (rtrn);
}

int	spawn_child_process(t_config *config, t_parse *cmd)
{
	pid_t	pid;

	if (cmd->next)
	{
		if (pipe(config->pipe) == -1)
			perror("pipe cmd");
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 2);
	if (pid == 0)
		run_child_process(config, cmd);
	ft_close(cmd->outfile);
	ft_close(config->saved_fd);
	if (cmd->next)
	{
		config->saved_fd = dup(config->pipe[0]);
		if (config->saved_fd == -1)
			perror("dup pipe[0]");
	}
	if (cmd->next)
	{
		ft_close(config->pipe[1]);
		ft_close(config->pipe[0]);
	}
	return (0);
}

int	redir_append(t_parse *cmd, char *file_name)
{
	if (is_directory(file_name))
		return (msg_error("minishell: ", file_name, ": Is a directory"), 1);
	safe_close(&cmd->outfile);
	cmd->outfile = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->outfile == -1)
		return (perror(file_name), -1);
	return (0);
}
