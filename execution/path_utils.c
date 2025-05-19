/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:10:12 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/19 18:13:49 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_path(char *str)
{
	if (!str)
		return (0);
	return (str[0] == '/' || (str[0] == '.' && (str[1] == '/' || str[1] == '.')) || str[0] == '.');
}

int	is_directory(char *str)
{
	struct stat st;

	if (!str)
		return (0);
	if (stat(str, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

int	is_file(char *str)
{
	struct stat st;

	if (!str)
		return (0);
	if (stat(str, &st) == -1)
		return (0);
	return (S_ISREG(st.st_mode));
}

char	*find_path(char *cmd_name, char **env)
{
	char	**paths;
	char	*dir;
	char	*cmd_path;
	char	*path;
	int		i;

	path = ft_getenv(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ":");
	if (!paths || !*paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		dir = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(dir, cmd_name);
		free(dir);
		if (!access(cmd_path, F_OK | X_OK))
			return (free(paths), cmd_path);
		free(cmd_path);
		i++;
	}
	return (free_array(paths), cmd_path);
}
