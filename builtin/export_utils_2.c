/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:12:19 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/25 22:12:40 by mouerchi         ###   ########.fr       */
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
