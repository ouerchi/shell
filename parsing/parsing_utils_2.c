/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:11:21 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/23 15:37:53 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_her(t_exp *exp)
{
	exp->j = 0;
	exp->res = NULL;
}

int	func_6_her(char *buff, t_exp *exp)
{
	if (buff[exp->j] == '$'
		&& (ft_isalnum(buff[exp->j + 1]) || buff[exp->j + 1] == '_'
			|| buff[exp->j + 1] == '$'))
		return (1);
	return (0);
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

int	validate_pipes(t_token *token, t_config *config, int flag, int exp_command)
{
	int		val;

	while (token)
	{
		if (func_4(token, &flag) == 1)
		{
			val = func_1(token, config, &flag);
			if (val == -1 || val == 0)
				return (val);
		}
		if (func_5(token) == 1)
		{
			if (func_2(token) == 0)
				return (0);
		}
		else if (token->type == T_PIPE)
		{
			if (func_3(token, &exp_command) == 0)
				return (0);
		}
		else
			exp_command = 0;
		token = token->next;
	}
	return (1);
}
