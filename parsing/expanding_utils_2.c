/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:57:18 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/25 20:47:26 by mouerchi         ###   ########.fr       */
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

char	*ft_strjoin_2(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*dst;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dst = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strcpy_join(dst, s1, s2);
	return (dst);
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
