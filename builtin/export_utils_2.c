/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:12:19 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/26 22:10:47 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_split_var(char ***var_array, char *env)
{
	*var_array = NULL;
	*var_array = ft_split_var(env);
	if (!(*var_array)[1])
		(*var_array)[1] = ft_strdup("");
}

void	update_shlvl(size_t *shlvl)
{
	char	*tmp;

	tmp = NULL;
	if (*shlvl >= 1000)
	{
		if (*shlvl <= 2147483647)
		{
			write(2, "minishell: warning: shell level ", 32);
			tmp = ft_itoa(*shlvl);
			write(2, tmp, ft_strlen(tmp));
			write(2, " too high, resetting to 1\n", 26);
			*shlvl = 1;
			free(tmp);
		}
		else
			*shlvl = 0;
	}
	return ;
}
