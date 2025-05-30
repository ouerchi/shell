/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 08:38:03 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/29 17:13:52 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_nl(char *str, int *i, int *j, int *newline)
{
	while (str[(*i)] && str[(*i)] == ' ')
		(*i)++;
	while (str[(*i)] && str[(*i)] == '-' && str[(*i) + 1] == 'n')
	{
		*j = *i;
		(*i)++;
		while (str[(*i)] && str[(*i)] == 'n')
			(*i)++;
		if ((str[(*i)] && str[(*i)] == ' ') ||!str[(*i)])
			*newline = 0;
		else
		{
			*i = *j;
			break ;
		}
		while (str[(*i)] && str[(*i)] == ' ')
			(*i)++;
	}
	return ;
}

int	check_toprint(char *str, int *i)
{
	if (str[(*i)] && str[(*i)] == '-' && str[(*i) + 1] == 'n')
	{
		(*i)++;
		while ((str[(*i)] && str[(*i)] == 'n')
			|| (str[(*i)] && str[(*i)] == ' '))
			(*i)++;
		if (!str[*i])
			return (0);
	}
	return (1);
}

static	void	print(char *str, int *i, int *newline)
{
	if (!*newline)
		printf("%s", str + (*i));
	else
		printf("%s\n", str + (*i));
}

static	void	no_print(int *newline)
{
	if (!*newline)
		printf("%c", '\0');
	else
		printf("\n");
}

int	ft_echo(char *str)
{
	int	i;
	int	j;
	int	x;
	int	newline;

	i = 0;
	j = 0;
	newline = 1;
	if (!str)
		return (1);
	check_nl(str, &i, &j, &newline);
	if (newline)
		i = j;
	x = i;
	if (!check_toprint(str, &i))
		no_print(&newline);
	else
	{
		i = x;
		print(str, &i, &newline);
	}
	return (0);
}
