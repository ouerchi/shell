/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   siganl_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:26:42 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/21 23:34:05 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int_handle(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

// void	sig_ign_handler(void)
// {
// 	struct sigaction	s;

// 	sigemptyset(&s.sa_mask);
// 	s.sa_flags = 0;
// 	s.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &s, NULL);
// }

// void	sig_int_handler(void)
// {
// 	struct sigaction	s;

// 	sigemptyset(&s.sa_mask);
// 	s.sa_flags = 0;
// 	s.sa_handler = sig_int_handle;
// 	sigaction(SIGINT, &s, NULL);
// }
