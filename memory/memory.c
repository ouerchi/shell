/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:36:44 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/26 15:19:37 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_files(t_files *files)
{
	t_files	*tmp;

	if (!files)
		return ;
	while (files)
	{
		tmp = files->next;
		free(files->name);
		free(files->type);
		free(files);
		files = tmp;
	}
	return ;
}

void	free_env_node(t_env *env)
{
	if (!env)
		return ;
	free(env->name);
	free(env->value);
	free(env->variable);
	free(env);
	return ;
}

void	free_env_lst(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env->next;
		free_env_node(env);
		env = tmp;
	}
}

void	free_lst(t_env **lst)
{
	free_env_lst(*lst);
	*lst = NULL;
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !(*arr))
		return ;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i++]);
	}
	free(arr);
	arr = NULL;
}
