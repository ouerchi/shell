/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:27:07 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/11 17:41:18 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (fd < 0 || !s)
		return ;
	i = 0;
	while (s[i] != '\0')
		ft_putchar_fd(s[i++], fd);
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*ft_strchr_q(char *s, int c, int c_2)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c || s[i] == (unsigned char)c_2)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0' || (unsigned char)c_2 == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
