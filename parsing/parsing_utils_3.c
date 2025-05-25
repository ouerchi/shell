/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:23:34 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/25 01:26:40 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	func_1(t_token *token, t_config *config, int *flag)
{
	int	val;

	val = ft_herdoc(config, token, flag);
	if (val == 0)
		return (-1);
	else if (val == -1)
		return (-2);
	return (1);
}

int	func_2(t_token *token)
{
	t_token	*next_token;

	next_token = token->next;
	if (!next_token)
		return (ft_putstr_fd("minishell: syntax error near unexpected token 'new\
line'\n", 2), exit_status(2, 0), 0);
	else if (next_token->type == T_PIPE)
		return (ft_putstr_fd("minishell: syntax error \
near unexpected token `|'\n", 2), exit_status(2, 0), 0);
	else if (next_token->type == T_REDIR_IN || next_token->type == T_REDIR_OUT \
		|| next_token->type == T_APPEND || next_token->type == T_HERDOC)
		return (printf("minishell: syntax error \
near unexpected token '%s'\n", next_token->value), exit_status(2, 0), 0);
	return (1);
}

int	func_3(t_token *token, int *expect_command)
{
	if ((*expect_command))
		return (ft_putstr_fd("minishell: syntax error \
near unexpected token `|'\n", 2), exit_status(2, 0), 0);
	else if (token->next == NULL)
		return (ft_putstr_fd("minishell: syntax error \
near unexpected token `|'\n", 2), exit_status(2, 0), 0);
	(*expect_command) = 1;
	return (1);
}

int	func_4(t_token *token, int *flag)
{
	if (token->next && token->type == T_HERDOC
		&& (token->next->type == T_WORD || token->next->type == T_RED)
		&& (*flag) == 0)
		return (1);
	return (0);
}

int	func_5(t_token *token)
{
	if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
		|| token->type == T_APPEND || token->type == T_HERDOC)
		return (1);
	return (0);
}
