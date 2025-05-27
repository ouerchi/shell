/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:07:25 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/27 19:32:39 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_token_list(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		free(lst->value);
		free(lst->exp);
		free(lst);
		lst = tmp;
	}
}

void	free_parse(t_parse **cmd)
{
	t_parse	*current;
	t_parse	*next;

	if (!cmd || !*cmd)
		return ;
	current = *cmd;
	while (current)
	{
		next = current->next;
		if (current->cmd_name)
			free(current->cmd_name);
		if (current->args)
			free_array(current->args);
		free(current);
		current = next;
	}
	*cmd = NULL;
}

void	free_utils(t_config *config)
{
	free_env_lst(config->env_lst);
	free_array(config->env);
}

void	ft_free_utils_2(t_config config, t_token *token, char *rl)
{
	ft_free_token_list(token);
	free_parse(&config.cmd);
	free(rl);
}

void	ft_free_utils_3(t_token *token, char *rl)
{
	ft_free_token_list(token);
	free(rl);
}
