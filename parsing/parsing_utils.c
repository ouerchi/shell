/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:45:36 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/24 20:12:59 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builtins_check(t_parse *par)
{
	if (!par || !par->cmd_name)
		return ;
	if ((ft_strlen(par->cmd_name) == ft_strlen("exit")) \
		&& (!ft_strncmp(par->cmd_name, "exit", ft_strlen(par->cmd_name))))
		par->builtins = 1;
	else if ((ft_strlen(par->cmd_name) == ft_strlen("echo")) \
		&& (!ft_strncmp(par->cmd_name, "echo", ft_strlen(par->cmd_name))))
		par->builtins = 1;
	else if ((ft_strlen(par->cmd_name) == ft_strlen("export")) \
		&& (!ft_strncmp(par->cmd_name, "export", ft_strlen(par->cmd_name))))
		par->builtins = 1;
	else if ((ft_strlen(par->cmd_name) == ft_strlen("cd")) \
		&& (!ft_strncmp(par->cmd_name, "cd", ft_strlen(par->cmd_name))))
		par->builtins = 1;
	else if ((ft_strlen(par->cmd_name) == ft_strlen("env")) \
		&& (!ft_strncmp(par->cmd_name, "env", ft_strlen(par->cmd_name))))
		par->builtins = 1;
	else if ((ft_strlen(par->cmd_name) == ft_strlen("pwd")) \
		&& (!ft_strncmp(par->cmd_name, "pwd", ft_strlen(par->cmd_name))))
		par->builtins = 1;
	else if ((ft_strlen(par->cmd_name) == ft_strlen("unset")) \
		&& (!ft_strncmp(par->cmd_name, "unset", ft_strlen(par->cmd_name))))
		par->builtins = 1;
	else
		par->builtins = 0;
}

int	count_words_before_pipe(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != T_PIPE)
	{
		if (token->type == T_WORD)
			count++;
		token = token->next;
	}
	return (count);
}

void	handle_redirection(t_token **check, t_parse **p)
{
	t_token_type	type;

	type = (*check)->type;
	*check = (*check)->next;
	if (!*check)
		return ;
	if (type == T_REDIR_IN)
		ft_lstadd_back_files(p, ft_files_new((*check)->value, "REDIR_IN"));
	else if (type == T_REDIR_OUT)
		ft_lstadd_back_files(p, ft_files_new((*check)->value, "REDIR_OUT"));
	else if (type == T_APPEND)
		ft_lstadd_back_files(p, ft_files_new((*check)->value, "APPEND"));
	else if (type == T_HERDOC)
		ft_lstadd_back_files(p, ft_files_new((*check)->value, "HERDOC"));
	*check = (*check)->next;
}

int	ft_find_her(t_token *token)
{
	t_token	*temp;
	int		count_her;

	temp = token;
	count_her = 0;
	while (temp)
	{
		if (temp->next && temp->type == T_HERDOC)
			count_her++;
		temp = temp->next;
	}
	return (count_her);
}

int	has_q_in_doll(char *buff)
{
	int	i;
	int	d_q;
	int	s_q;

	i = 0;
	d_q = 0;
	s_q = 0;
	while (buff[i] && buff[i] != '$')
	{
		if (buff[i] == '"' && d_q == 1)
			d_q = 0;
		else if (buff[i] == '"' && d_q == 0 && s_q == 0)
			d_q = 1;
		else if (buff[i] == '\'' && s_q == 1)
			s_q = 0;
		else if (buff[i] == '\'' && s_q == 0 && d_q == 0)
			s_q = 1;
		i++;
	}
	if (d_q == 0 && s_q == 0)
		return (1);
	return (0);
}
