/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:34:07 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/25 20:26:12 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_process(t_config *config)
{
	config->pids = NULL;
	config->cmd_idx = 0;
	config->saved_fd = -1;
}

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

void	parent(t_config *config)
{
	int		status;
	t_pid	*pid;

	signal(SIGINT, sig_parent_handler);
	pid = config->pids;
	while (pid)
	{
		if (waitpid(pid->pid, &status, 0) == -1)
			perror(strerror(errno));
		else
		{
			if (WIFEXITED(status))
				exit_status(WEXITSTATUS(status), 0);
			if (WIFSIGNALED(status))
				exit_status(WTERMSIG(status) + 128, 0);
		}	
		pid = pid->next;
	}
	free_pids(&config->pids);
}

int	exit_status(int status, int flag)
{
	static int	exit_status;

	if (flag != 1)
		exit_status = status;
	return (exit_status);
}
