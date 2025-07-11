/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:23:31 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/23 20:27:04 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_handle_buff(char *rl, int *i)
{
	char	*buff;
	char	quote;

	buff = NULL;
	while (rl[*i] && !ft_strchr(" >|<", rl[(*i)]))
	{
		if (rl[(*i)] == '\'' || rl[(*i)] == '"')
		{
			quote = rl[(*i)];
			buff = ft_strjoin_char(buff, quote);
			((*i))++;
			while (rl[(*i)] && rl[(*i)] != quote)
				buff = ft_strjoin_char(buff, rl[((*i))++]);
			if (rl[(*i)] == quote)
			{
				buff = ft_strjoin_char(buff, quote);
				(*i)++;
			}
		}
		else
			buff = ft_strjoin_char(buff, rl[(*i)++]);
	}
	return (buff);
}

int	handle_char(t_dec *dec, char *rl, int *i)
{
	if (!dec->quote && (rl[*i] == '\'' || rl[*i] == '"'))
	{
		dec->quote = rl[(*i)++];
		return (1);
	}
	if (dec->quote && rl[*i] == dec->quote)
	{
		dec->quote = 0;
		(*i)++;
		return (1);
	}
	if (!dec->quote && ft_strchr(">|< \t", rl[*i]))
		return (0);
	dec->temp = ft_strjoin_char(dec->buff, rl[(*i)++]);
	if (!dec->temp)
		return (0);
	dec->buff = ft_strdup(dec->temp);
	free(dec->temp);
	return (1);
}

char	*ft_handle_words(char *rl, int i)
{
	t_dec	dec;

	dec.quote = 0;
	dec.buff = NULL;
	while (rl[i])
	{
		if (!handle_char(&dec, rl, &i))
			break ;
	}
	return (dec.buff);
}

t_quotes_state	ft_handle_quotes(char *rl)
{
	int				i;
	t_quotes_state	state;

	i = 0;
	state = NONE;
	while (rl[i])
	{
		if (rl[i] == '\\' && state != S_QUOTES)
		{
			i++;
			continue ;
		}
		if (state == NONE)
		{
			if (rl[i] == '\'')
				state = S_QUOTES;
			else if (rl[i] == '"')
				state = D_QUOTES;
		}
		else if ((state == S_QUOTES && rl[i] == '\'')
			|| (state == D_QUOTES && rl[i] == '"'))
			state = NONE;
		i++;
	}
	return (state);
}

t_error_type	ft_handle_error(char *rl)
{
	t_quotes_state	state_quotes;

	state_quotes = ft_handle_quotes(rl);
	if (state_quotes != NONE)
		return (ERR_UNCLOSED_QUOTES);
	return (ERR_NONE);
}
