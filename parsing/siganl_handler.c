/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   siganl_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:26:42 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/23 16:19:23 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int_handle(int sig)
{
	char  new;

	(void)sig;
	new = '\n';
	rl_replace_line("", 0);
    rl_on_new_line();
    ioctl(0, TIOCSTI, &new);
	exit_status(130, 0);
}
