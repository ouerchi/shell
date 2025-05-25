/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   siganl_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:26:42 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/25 22:10:59 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int_handle(int sig)
{
	(void)sig;
	write(1, "\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit_status(130, 0);
}

void	sig_parent_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	sig_handler_her(int sig)
{
	const char	c = '\n';

	(void)sig;
	g_global_her = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	ioctl(0, TIOCSTI, &c);
	exit_status(130, 0);
}

void	ft_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handle);
}

void	ft_re_init_her(t_config *config)
{
	config->flag_c = -101;
	g_global_her = 0;
}
