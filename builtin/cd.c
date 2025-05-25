/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:59:18 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/25 21:58:23 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_cd_error(void)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

static int	goto_home_dir(char **env)
{
	int		res;
	char	*env_value;

	env_value = ft_getenv(env, "HOME");
	if (!env_value)
		return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	res = chdir(env_value);
	if (res < 0)
		return (print_cd_error(), 1);
	return (0);
}

static int	goto_prev_dir(char **env)
{
	int		res;
	char	*env_value;

	env_value = ft_getenv(env, "OLDPWD");
	if (!env_value)
	{
		ft_putstr_fd("cd: OLDPWD not set", 2);
		return (1);
	}
	res = chdir(env_value);
	if (res < 0)
	{
		print_cd_error();
		return (1);
	}
	return (0);
}

static int	ft_cd_utils(int cd_rtrn)
{
	if (cd_rtrn < 0)
	{
		print_cd_error();
		return (1);
	}
}

int	ft_cd(char *path, char **env, int *cd_broken)
{
	char	*cwd;
	int		cd_rtrn;

	if (!path)
		return (goto_home_dir(env));
	cwd = getcwd(NULL, 0);
	if (!cwd && !ft_strcmp(path, "..") && !(*cd_broken))
	{
		write(2, "minishell : cd: ..: No such file or directory\n", 47);
		(*cd_broken) = 1;
		return (1);
	}
	if (!cwd && !ft_strcmp(path, "..") && (*cd_broken) == 1)
		return (cd_rtrn = chdir(path), -1);
	if (!ft_strcmp(path, "-"))
		cd_rtrn = goto_prev_dir(env);
	else
	{
		cd_rtrn = chdir(path);
		if (ft_cd_utils(cd_rtrn))
			return (free(cwd), 1);
	}
	free(cwd);
	return (0);
}
