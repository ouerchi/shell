/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:27:46 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/22 18:10:47 by mouerchi         ###   ########.fr       */
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

bool	ft_over_check(char *str)
{
	bool	flag;

	flag = false;
	ft_atoi(str, &flag);
	return (flag);
}

int	ft_exit(char **arg, int child_flag)
{
	int	exit_status;
	bool flag;

	if (!arg[1])
	{
		if (child_flag == 0)
			write(2, "exit\n", 5);
		exit(0);
	}
	if ((arg[1] && !ft_isdigits(arg[1])) || ft_over_check(arg[1]))
	{
		if (child_flag == 0)
			write(2, "exit\n", 5);
		write(2, "minishell: exit: ", ft_strlen("minishell: exit: "));
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, ": numeric argument required\n", ft_strlen(": numeric argument required\n"));
		// free_all;
		exit(2);
	}
	if (arg[1] && arg[2])
	{
		if (child_flag == 0)
			write(2, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", ft_strlen("minishell: exit: too many arguments\n"));
		return (1);
	}
	exit_status = ft_atoi(arg[1], &flag);
	exit_status %= 256;
	if (child_flag == 0)
		write(2, "exit\n", 5);
	// free_all;
	exit(exit_status);
}


/*

check if arg[1] == -1
if flag = true  ==> numeric argument required
else ==> nothing

*/