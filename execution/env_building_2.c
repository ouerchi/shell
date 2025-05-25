/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_building_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:22:18 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/25 21:44:00 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_var(t_env **node, t_env ***lst, char *var, char ***split_var)
{
	*node = NULL;
	*split_var = NULL;
	*node = (t_env *)malloc(sizeof(t_env));
	if (!*node)
		return (free_lst(*lst));
	*split_var = ft_split_var(var);
}

void	succes_split(t_env **node, char ***split_var)
{
	(*node)->name = (*split_var)[0];
	(*node)->value = (*split_var)[1];
}

void	fail_split(t_env **node, char *var)
{
	(*node)->name = var;
	(*node)->value = NULL;
}

void	append_env_lst(t_env **lst, char *variable)
{
	t_env	*node;
	t_env	*current;
	char	**splited_var;

	if (!lst || !variable)
		return ;
	init_var(&node, &lst, variable, &splited_var);
	if (splited_var)
		succes_split(&node, &splited_var);
	else
		fail_split(&node, ft_strdup(variable));
	node->variable = ft_strdup(variable);
	node->next = NULL;
	free(splited_var);
	if (!(*lst))
	{
		*lst = node;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = node;
}

int	ft_update_pwd(t_config *config)
{
	char	*old_pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	old_pwd = ft_getenv(config->env, "PWD");
	if (old_pwd)
		ft_setenv(config, "OLDPWD", ft_strdup(old_pwd));
	else
		ft_setenv(config, "OLDPWD", NULL);
	ft_setenv(config, "PWD", ft_strdup(cwd));
	update_env_array(config);
	free(cwd);
	return (0);
}
