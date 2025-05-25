/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:11:21 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/25 22:10:50 by mouerchi         ###   ########.fr       */
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

char	*ft_handle_words_her(char *rl)
{
	int		i;
	t_dec	dec;

	i = 0;
	dec.quote = 0;
	dec.buff = NULL;
	while (rl[i])
	{
		if (!handle_char(&dec, rl, &i))
			break ;
	}
	return (dec.buff);
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
