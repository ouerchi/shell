/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:48:41 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/25 20:30:53 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	can_expand_variable(char *buff, t_q *q, t_exp *exp)
{
	if (buff[exp->j] == '$' && buff[exp->j + 1] != '\''
		&& buff[exp->j + 1] != '"' && q->single_q == 0
		&& (ft_isalnum(buff[exp->j + 1]) || buff[exp->j + 1] == '_'
			|| buff[exp->j + 1] == '$'))
		return (1);
	return (0);
}

int	is_dollar_before_quote(char *buff, t_q *q, t_exp *exp)
{
	if (buff[exp->j] == '$' && (buff[exp->j + 1] == '\''
			|| buff[exp->j + 1] == '"') && q->single_q == 0
		&& q->double_q == 0)
		return (1);
	return (0);
}

char	*ft_word(char *buff, t_config *config, int *flag)
{
	char	*dup;
	t_exp	exp;
	t_q		quotes;

	dup = NULL;
	if (has_doll(buff) == 0)
	{
		(*flag) = 1;
		init_queen(&exp, &quotes);
		dup = expand_variables(buff, config, exp, quotes);
		config->isexpanded = 1;
	}
	else
		dup = ft_handle_words(buff, 0);
	return (dup);
}
