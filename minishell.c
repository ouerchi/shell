/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:55:20 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/23 19:48:45 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state_loop	ft_state_loop(t_token *token, t_config *config)
{
	config->cmd = parse_piped_commands(&token, config);
	if (!config->cmd)
		return (free_parse(config->cmd), CONTINUE);
	else
	{
		// ft_print_list(config->cmd);
		execution(config);
		return (CONTINUE);
	}
}

int	ft_break(t_token *token, t_config *config)
{
	int	val;

	val = validate_pipes(token, config, 0, 1);
	if (val == 1 || val == -1)
	{
		if (ft_ambi(token, config, 0, 0) == 1)
			return (1);
		if (ft_state_loop(token, config) == BREAK)
			return (free_parse(config->cmd), 0);
		if (val == -1)
			return (0);
	}
	else
	{
		config->flag_2 = 0;
		config->amb = 0;
	}
	return (1);
}

int	ft_continue(char *rl)
{
	t_error_type	state;

	state = ft_handle_error(rl);
	if (state == ERR_UNCLOSED_QUOTES)
	{
		ft_putstr_fd("minishell: Syntax error: Unclosed quotes\n", 2);
		exit_status(2, 0);
		return (0);
	}
	return (1);
}

void	minishell_loop(t_config config)
{
	char		*rl;
	t_token		*token;

	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handle);
	while (1)
	{
		rl = readline("minishell-$ ✗ ");
		if (!rl)
		{
			printf("exit\n");
			break ;
		}
		add_history(rl);
		if (ft_continue(rl) == 0)
			continue ;
		token = ft_add_cmd(rl, &config);
		if (ft_break(token, &config) == 0)
			break ;
		ft_free_token_list(token);
		free_parse(config.cmd);
		free(rl);
	}
	free_env_lst(config.env_lst);
	free_array(config.env);
}

int	main(int argc, char **argv, char **env)
{
	t_config	config;

	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		printf("not runnig...\n");
		printf("try again!\n");
		exit(0);
	}
	if (argc == 1)
	{
		init_env(&config, env);
		minishell_loop(config);
	}
	else
		return (printf("minishell: %s: No such file \
or directory\n", argv[1]), exit_status(127, 0));
	return (exit_status(-1, 1));
}
