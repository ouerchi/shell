/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:42 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/22 18:12:33 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	digit_count(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count = 1;
		n = n * -1;
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static int	converte(char *ascii, int n, int i)
{
	if (n >= 10)
	{
		i = converte(ascii, n / 10, i);
	}
	ascii[i] = (n % 10) + '0';
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char	*ascii;
	int		i;

	i = 0;
	if (n == -2147483648 || n == 0)
	{
		if (n == 0)
			return (ft_strdup("0"));
		else
			return (ft_strdup("-2147483648"));
	}
	ascii = malloc(digit_count(n) + 1);
	if (ascii == NULL)
		return (NULL);
	if (n < 0)
	{
		ascii[0] = '-';
		n = -n;
		i = 1;
	}
	i = converte(ascii, n, i);
	ascii[i] = '\0';
	return (ascii);
}

static int	check_sign(int sign, bool *flag)
{
	*flag = true;
	if (sign < 0)
		return (0);
	else
		return (-1);
}

long long	ft_atoi(const char *str, bool *flag)
{
	long long	result;
	long long	old_result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		old_result = result;
		result = result * 10 + (sign * (str[i] - '0'));
		if ((result / 10) != old_result)
			return (check_sign(sign, flag));
		i++;
	}
	return (result);
}