/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:47:03 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/25 22:09:00 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_global_her = 0;

static char	*ft_expanding_her(t_her *her, t_config *config, t_exp exp)
{
	exp.count = ft_calc_dol(her->rl_her, 0) % 2;
	if (has_q(her->rl_her) == 1 && exp.count == 1 && !has_doll_2(her->rl_her))
		return (ft_strdup("$"));
	while (her->rl_her[exp.j])
	{
		if (her->rl_her[exp.j] == '$'
			&& is_numeric_char(her->rl_her, exp.j + 1) && (her->flag == 0))
			exp.j += 2;
		else if (her->rl_her[(exp.j)] == '$' && her->rl_her[exp.j + 1] == '?'
			&& (her->flag == 0))
		{
			exp.j += 2;
			exp.res = ft_strjoin_free(exp.res, ft_itoa(exit_status(-1, 1)));
		}
		else if (her->rl_her[exp.j] == '$' && her->rl_her[exp.j + 1] == '\0'
			&& (her->flag == 0))
			exp.res = ft_strjoin_char(exp.res, her->rl_her[exp.j++]);
		else if (func_6_her(her->rl_her, &exp) && (her->flag == 0))
			exp.res = third(her->rl_her, config, exp, &exp.j);
		else
			exp.res = ft_strjoin_char(exp.res, her->rl_her[exp.j++]);
	}
	return (ft_strjoin_char(exp.res, '\n'));
}

void	ft_herdoc_4(t_token *token, t_her *her, t_config *config, t_exp *exp)
{
	signal(SIGINT, sig_handler_her);
	her->rl_her = readline("> ");
	while (her->rl_her)
	{
		if (g_global_her == 1)
		{
			ft_re_init_her(config);
			break ;
		}
		if (has_q(token->next->exp) == 0)
			her->flag = 1;
		her->temp = ft_handle_words_her(token->next->exp);
		if (ft_strcmp_her(her->rl_her, her->temp) == INT_MIN
			|| !ft_strcmp_her(her->rl_her, her->temp))
		{
			free(her->temp);
			break ;
		}
		her->check = ft_expanding_her(her, config, *exp);
		write(her->fd, her->check, ft_strlen(her->check));
		free(her->check);
		free(her->temp);
		her->rl_her = readline("> ");
	}
	signal(SIGINT, sig_int_handle);
}

int	ft_herdoc_2(t_token *token, t_her *her, t_config *config)
{
	t_exp	exp;

	init_her(&exp);
	her->name = ft_gen_name_file();
	if (!her->name)
		return (-1);
	her->fd = open(her->name, O_CREAT | O_TRUNC | O_RDWR, 0777);
	her->fd_beg = open(her->name, O_RDWR);
	unlink(her->name);
	free(her->name);
	ft_herdoc_4(token, her, config, &exp);
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
	while (token && token->next)
	{
		if (ft_herdoc_3(token, config, &her, &name) == -1)
			return (-1);
		token = token->next;
	}
	return ((config->her_name = name), 1);
}

int	ft_herdoc_3(t_token *token, t_config *config, t_her *her, t_name **name)
{
	t_name	*name_new;

	if (token->next && token->type == T_HERDOC
		&& (token->next->type == T_WORD || token->next->type == T_RED)
		&& (her->count_per > 0))
	{
		if (her->fd != -1)
			close(her->fd);
		if (ft_herdoc_2(token, her, config) == -1)
			return (ft_free_name_list(*name), -1);
		if (config->flag_c == -101)
			return (ft_free_name_list(*name), config->flag_c = 0, -1);
		name_new = ft_name_new(her->fd_beg);
		ft_lstadd_back_name(name, name_new);
		her->count_per--;
	}
	return (1);
}
