/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:55:11 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/26 00:09:54 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while ((str1[i] || str2[i]) && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

static char	*ft_stchar_utils(char c)
{
	char	*dst;

	dst = (char *)malloc(2 * sizeof(char));
	if (!dst)
		return (NULL);
	dst[0] = c;
	dst[1] = '\0';
	return (dst);
}

char	*ft_strjoin_char(char *s1, char c)
{
	int		i;
	int		len;
	char	*dst;

	if (!s1)
		return (ft_stchar_utils(c));
	len = ft_strlen(s1);
	dst = (char *)malloc((len + 2) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i++] = c;
	dst[i] = '\0';
	free(s1);
	return (dst);
}

void	ft_strcpy_join(char *dst, char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	while (i < len_s1)
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len_s2)
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*dst;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dst = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strcpy_join(dst, s1, s2);
	free(s1);
	return (dst);
}
