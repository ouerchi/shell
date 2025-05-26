/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:57:18 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/26 00:18:43 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_handle_name(char *buff, int *i)
{
	char	*temp;

	temp = NULL;
	(*i)++;
	if (buff[(*i)] && buff[(*i)] == '$')
		(*i)++;
	else
	{
		while (buff[(*i)] && (ft_isalnum(buff[(*i)]) || buff[(*i)] == '_'))
			temp = ft_strjoin_char(temp, buff[(*i)++]);
	}
	return (temp);
}

char	*ft_handle_name_her(char *buff, int *i)
{
	char	*temp;

	temp = NULL;
	(*i)++;
	while (buff[(*i)] && (ft_isalnum(buff[(*i)]) || buff[(*i)] == '_'))
		temp = ft_strjoin_char(temp, buff[(*i)++]);
	return (temp);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	new_str = ft_strjoin_2(s1, s2);
	free(s1);
	free(s2);
	return (new_str);
}

int	has_doll(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

int	ft_isspace(char *rl)
{
	int	i;

	i = 0;
	while (rl[i] && (rl[i] == ' ' || rl[i] == '\t'))
		i++;
	if (!rl[i])
		return (0);
	return (1);
}
