/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:27:46 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/21 19:20:16 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static int	ft_isdigits(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	if (!str[i])
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (!str[i]);
}

int	ft_exit(char **arg, int child_flag)
{
	int	exit_status;

	if (!arg[1])
	{
		if (child_flag == 0)
			ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	if ((arg[1] && !ft_isdigits(arg[1])) || ft_strlen(arg[1]) > 19)
	{
		if (child_flag == 0)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		// free_all;
		exit(2);
	}
	if (arg[1] && arg[2])
	{
		if (child_flag == 0)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		return (1);
	}
	exit_status = ft_atoi(arg[1]);
	exit_status %= 256;
	if (child_flag == 0)
		ft_putstr_fd("exit\n", 2);
	// free_all;
	exit(exit_status);
}
