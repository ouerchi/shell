/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:55:20 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/28 18:35:08 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_state_loop(t_token *token, t_config *config)
{
	config->cmd = parse_piped_commands(&token, config);
	if (!config->cmd)
		return ;
	else
	{
		execution(config);
		free_parse(&config->cmd);
		return ;
	}
}

int	ft_break(t_token *token, t_config *config)
{
	int	val;

	val = validate_pipes(token, config, 0, 1);
	if (val == -1)
		return (0);
	if (val == -2)
		return (1);
	else if (val == 1)
		ft_state_loop(token, config);
	else if (val == 0 && config->her_name)
		ft_free_name_list(config->her_name);
	return (1);
}

int	ft_continue(char *rl)
{
	t_error_type	state;

	state = ft_handle_error(rl);
	if (state == ERR_UNCLOSED_QUOTES)
	{
		write(2, "minishell: Syntax error: Unclosed quotes\n", 41);
		exit_status(2, 0);
		return (0);
	}
	return (1);
}

void	minishell_loop(t_config config, t_token *token, char *rl)
{
	while (1)
	{
		ft_signal();
		rl = readline("minishell-$ ✗ ");
		if (!rl)
		{
			printf("exit\n");
			break ;
		}
		if (!empty_rl(rl))
			continue ;
		add_history(rl);
		if (ft_continue(rl) == 0)
			continue ;
		token = ft_add_cmd(rl, &config);
		if (ft_break(token, &config) == 0)
		{
			ft_free_utils_2(config, token, rl);
			break ;
		}
		ft_free_utils_3(token, rl);
	}
	rl_clear_history();
	free_utils(&config);
}

int	main(int argc, char **argv, char **env)
{
	char		*rl;
	t_token		*token;
	t_config	config;

	rl = NULL;
	token = NULL;
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		printf("not runnig...\n");
		printf("try again!\n");
		exit(0);
	}
	if (argc == 1)
	{
		init_env(&config, env);
		minishell_loop(config, token, rl);
	}
	else
		return (printf("minishell: %s: No such file \
or directory\n", argv[1]), exit_status(127, 0));
	return (exit_status(-1, 1));
}
