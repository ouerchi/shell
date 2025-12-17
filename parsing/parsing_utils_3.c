/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:23:34 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/27 00:22:13 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	validate_heredoc(t_token *token, t_config *config, int *flag)
{
	int	val;

	val = ft_herdoc(config, token, flag);
	if (val == 0)
		return (-1);
	else if (val == -1)
		return (-2);
	return (1);
}

int	check_next_token_validity(t_token *token)
{
	t_token	*next_token;

	next_token = token->next;
	if (!next_token)
	{
		write(2, "minishell: syntax error near unexpected token 'new\
line'\n", 56);
		return (exit_status(2, 0), 0);
	}
	else if (next_token->type == T_PIPE)
	{
		write(2, "minishell: syntax error \
near unexpected token `|'\n", 50);
		return (exit_status(2, 0), 0);
	}
	else if (next_token->type == T_REDIR_IN || next_token->type == T_REDIR_OUT \
		|| next_token->type == T_APPEND || next_token->type == T_HERDOC)
	{
		write(2, "minishell: syntax error near unexpected token ", 46);
		write(2, "'", 1);
		write(2, next_token->value, ft_strlen(next_token->value));
		write(2, "'\n", 2);
		return (exit_status(2, 0), 0);
	}
	return (1);
}

int	check_pipe_position(t_token *token, int *expect_command)
{
	if ((*expect_command))
	{
		write(2, "minishell: syntax error \
near unexpected token `|'\n", 50);
		return (exit_status(2, 0), 0);
	}
	else if (token->next == NULL)
	{
		write(2, "minishell: syntax error \
near unexpected token `|'\n", 50);
		return (exit_status(2, 0), 0);
	}
	(*expect_command) = 1;
	return (1);
}

int	is_heredoc_sequence(t_token *token, int *flag)
{
	if (token->next && token->type == T_HERDOC
		&& (token->next->type == T_WORD || token->next->type == T_RED)
		&& (*flag) == 0)
		return (1);
	return (0);
}

int	is_redirection(t_token *token)
{
	if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
		|| token->type == T_APPEND || token->type == T_HERDOC)
		return (1);
	return (0);
}
