/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:47:03 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/19 21:47:24 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_expanding_her(char *rl_her, t_config *config, int *flag)
{
	int			j;
	t_exp		exp;

	j = 0;
	exp.res = NULL;
	while (rl_her[j])
	{
		if (rl_her[j] == '$' && is_numeric_char(rl_her, j + 1) && (*flag) == 0)
			j += 1;
		else if (rl_her[j] == '$' && ((*flag) == 0))
		{
			exp.temp_var = ft_handle_name_her(rl_her, &j);
			exp.temp_val = ft_search_lst(config, exp.temp_var);
			exp.res = ft_strjoin_free(exp.res, exp.temp_val);
			free(exp.temp_var);
		}
		else
			exp.res = ft_strjoin_char(exp.res, rl_her[j]);
		j++;
	}
	exp.res = ft_strjoin_char(exp.res, '\n');
	return (exp.res);
}

static char	*ft_handle_words_her(char *rl)
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

int	ft_herdoc_2(t_token *token, t_her *her, t_config *config)
{
	her->name = ft_gen_name_file();
	if (!her->name)
		return (-1);
	her->fd = open(her->name, O_CREAT | O_TRUNC | O_RDWR, 0777);
	her->fd_beg = open(her->name, O_RDWR);
	unlink(her->name);
	her->rl_her = readline("> ");
	while (her->rl_her)
	{
		if (has_q(token->next->exp) == 0)
			her->flag = 1;
		her->temp = ft_handle_words_her(token->next->exp);
		if (ft_strcmp_her(her->rl_her, her->temp) == INT_MIN
			|| !ft_strcmp_her(her->rl_her, her->temp))
			break ;
		her->check = ft_expanding_her(her->rl_her, config, &her->flag);
		write(her->fd, her->check, ft_strlen(her->check));
		her->rl_her = readline("> ");
	}
	her->flag = 0;
	return (1);
}

int	ft_herdoc(t_config *config, t_token *token, int *flag)
{
	t_her	her;
	t_name	*name;

	her.flag = 0;
	her.fd = -1;
	her.fd_beg = -1;
	her.count_per = 0;
	name = NULL;
	if (extra_her(token, &her) == 0)
		return (0);
	(*flag) = 1;
	while (token)
	{
		while (token && token->type != T_PIPE)
		{
			if (ft_herdoc_3(token, config, &her, &name) == -1)
				return (-1);
			token = token->next;
		}
		if (token)
			token = token->next;
		else
			break ;
	}
	config->her_name = name;
	return (1);
}

int	ft_herdoc_3(t_token *token, t_config *config, t_her *her, t_name **name)
{
	if (token->next && token->type == T_HERDOC
		&& token->next->type == T_WORD && (her->count_per > 0))
	{
		close(her->fd);
		if (ft_herdoc_2(token, her, config) == -1)
			return (ft_free_name_list(*name), -1);
		ft_lstadd_back_name(name, ft_name_new(her->fd_beg));
		her->count_per--;
	}
	return (1);
}
