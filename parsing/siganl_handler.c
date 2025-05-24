/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   siganl_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:26:42 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/24 22:40:48 by mouerchi         ###   ########.fr       */
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
