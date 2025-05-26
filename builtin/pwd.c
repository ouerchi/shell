/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:15:26 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/26 18:42:03 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_config *config)
{
	char	*cwd;
	char	*tmp;

	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		tmp = NULL;
		tmp = ft_strdup(ft_getenv(config->env, "PWD"));
		printf("%s\n", tmp);
		free(tmp);
		return (1);
	}
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	free (cwd);
	return (0);
}
