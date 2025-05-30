/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:10:12 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/30 20:23:14 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(char *str)
{
	struct stat	st;

	if (!str)
		return (0);
	if (stat(str, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
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
	if (!paths[1])
		return (handel_one_path(paths, cmd_name));
	i = -1;
	while (paths[++i])
	{
		dir = ft_strjoin_2(paths[i], "/");
		cmd_path = ft_strjoin(dir, cmd_name);
		if (!access(cmd_path, F_OK | X_OK))
			return (free_array(paths), cmd_path);
		free(cmd_path);
	}
	return (free_array(paths), cmd_name);
}

void	ft_ft_close(int out, int in, int save)
{
	ft_close(out);
	ft_close(in);
	ft_close(save);
}

int	ft_check_points(t_config *config, char *cmd)
{
	if (ft_strlen(cmd) == 1 && cmd[0] == '.')
		return (exit_status(2, 0),
			error_handling(1, cmd, \
				": filename argument required", 2), 2);
	else if (!ft_strncmp(cmd, "..", 2) && ft_strchr(cmd, '/'))
		return (check_cmd(config, cmd));
	else if (!ft_strncmp(cmd, "..", 2))
		return (0);
	return (1);
}
