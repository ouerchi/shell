/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:12:15 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/26 17:14:26 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_add_cmd(char *rl, t_config *config)
{
	int		i;
	t_token	*lst;

	i = 0;
	lst = NULL;
	while (rl[i])
	{
		while (rl[i] == ' ' || rl[i] == '\t')
			i++;
		if (!rl[i])
			break ;
		process_char(rl, &i, &lst, config);
	}
	return (lst);
}

t_parse	*ft_parsing(t_token **token, t_config *config)
{
	int		i;
	char	**arg;
	t_parse	*parse;

	parse = ft_parse_new();
	if (!parse)
		return (NULL);
	config->cmd = parse;
	arg = ft_check_parse(token, &config, &i);
	if (!arg)
	{
		free_parse(&parse);
		return (NULL);
	}
	parse->args = arg;
	if (i > 0)
		parse->cmd_name = ft_strdup(arg[0]);
	else
		parse->cmd_name = NULL;
	ft_builtins_check(parse);
	return (parse);
}

char	**ft_check_parse(t_token **check, t_config **config, int *i)
{
	char	**arg;
	
	if (!count_words_before_pipe(*check))
		return (NULL);
	arg = (char **)malloc(sizeof(char *) * \
	(count_words_before_pipe(*check) + 1));
	if (!arg)
		return (NULL);
	*i = 0;
	while ((*check) && ((*check)->type != T_PIPE))
	{
		if ((*check)->type == T_REDIR_IN || (*check)->type == T_REDIR_OUT
			|| (*check)->type == T_APPEND || (*check)->type == T_HERDOC)
			handle_redirection(check, &(*config)->cmd);
		else if ((*check)->type == T_WORD)
		{
			arg[(*i)++] = ft_strdup((*check)->value);
			if ((*check))
				(*check) = (*check)->next;
		}
		else
			(*check) = (*check)->next;
	}
	arg[(*i)] = NULL;
	return (arg);
}

t_parse	*parse_piped_commands(t_token **token_p, t_config *config)
{
	t_parse	*cmd;
	t_token	*token;

	cmd = ft_parsing(token_p, config);
	if (!cmd)
		return (NULL);
	token = *token_p;
	if (token && token->type == T_PIPE)
	{
		*token_p = token->next;
		cmd->next = parse_piped_commands(token_p, config);
		if (!cmd->next && *token_p)
			return (NULL);
	}
	return (cmd);
}

int	validate_pipes(t_token *token, t_config *config, int flag, int exp_command)
{
	int		val;

	while (token)
	{
		if (func_4(token, &flag) == 1)
		{
			val = func_1(token, config, &flag);
			if (val == -1 || val == -2)
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
