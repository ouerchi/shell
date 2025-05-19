/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:34:50 by mouerchi          #+#    #+#             */
/*   Updated: 2025/05/19 15:10:10 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_no_args(char **args, char **env)
{
	int	i;

	if (!args || !env)
		return (1);
	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}		
	return (0);
}

void	msg_error(char *msg1, char *full, char *msg2)
{
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(full, 2);
	ft_putstr_fd(msg2, 2);
}

int	is_valid_char(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (0);
	return (1);
}

int	valid_var_name(char *name, char *full)
{
	int i;

	if (!name[0] || (!ft_isalpha(name[0])&& name[0] != '_'))
	{
		msg_error("minishell: export: `", full, "' : not a valid identifier\n");
		return (1);
	}
	i = 0;
	while (name[i] && name[i] != '+')
	{
		if (!is_valid_char(name[i]))
		{
			msg_error("minishell: export: `", full, "' : not a valid identifier\n");
			return (1);			
		}
		i++;
	}
	if (name[i] == '+' && name[i + 1] != '\0')
	{
		msg_error("minishell: export: `", full, "' : not a valid identifier\n");
		return (1);		
	}
	return (0);
}

// int	ft_isspace(char c)
// {
// 	if (c == ' ' || c == '\t')
// 		return (1);
// 	return (0);
// }

// char	*process_value_helper(char *value, char *lead_space, char *end_space)
// {
// 	char	**split_value;
// 	char	*join_value;
	
// 	split_value = ft_split(value, " \t");
// 	if (!split_value)
// 		return (free(lead_space), free(end_space), NULL);
// 	join_value = array_join(split_value);
// 	free_array(split_value);
// 	join_value = ft_strjoin(join_value, end_space);
// 	if (!join_value)
// 		return (free(lead_space), free(end_space), NULL);
// 	free(end_space);
// 	join_value = ft_strjoin(lead_space, join_value);
// 	if (!join_value)
// 		return (free(lead_space), free(end_space), NULL);
// 	free(lead_space);
// 	return (join_value);
// }

// char	*process_value(char *value)
// {
// 	int		i;
// 	char	*lead_space;
// 	char	*end_space;

// 	i = 0;
// 	while (value[i] && ft_isspace(value[i]))
// 		i++;
// 	lead_space = ft_substr(value, 0, i);
// 	if (!lead_space)
// 		return (NULL);
// 	if (value[i])
// 	{
// 		i = ft_strlen(value) - 1;
// 		while (i >= 0 && ft_isspace(value[i]))
// 			i--;
// 		end_space = ft_substr(value, i + 1, ft_strlen(value));
// 	}
// 	else
// 		end_space = ft_strdup("");
// 	if (!end_space)
// 		return (free(lead_space), NULL);
// 	return (process_value_helper(value, lead_space, end_space));
// }

int	export_args(t_config *config, char *arg, char *name)
{
	char	*value;
	char	*full;
	char	*equal_sign;

	(void)config;
	full = ft_strdup(arg);
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		name = arg;
		if (valid_var_name(name, full))
			return (free(full), free(arg), 1);
		value = equal_sign + 1;
		printf("value = %s\n", value);
		// value = process_value(value);
		ft_setenv(config, name, ft_strdup(value));
	}
	if (!equal_sign && !valid_var_name(arg, full))
		ft_setenv(config, arg, NULL);
	else if (!equal_sign)
		return (1);
	free(arg);
	free(full);
	return (0);
}

int	ft_export(t_config *config, char **args)
{
	char	**env;
	char	*name;
	int		i;

	name = NULL;
	env = config->env;
	if (!args[1])
		return (if_no_args(args, env));
	i = 1;
	while (args[i])
	{
		if (export_args(config, ft_strdup(args[i]), name))
			return (1);
		i++;
	}
	return (0);
}

/*

equal_pos = srch for '='

name =  

value = equal_pos + 1;



char	*normalize_helper(char *value, char *leading_spaces, char *ending_spaces)
{
	char	**split_value;
	char	*res;

	split_value = ft_split_set(value, " \t");
	if (!split_value)
		return (NULL);
	res = join_array(split_value, true);
	res = ft_strjoin(res, ending_spaces);
	free(ending_spaces);
	ending_spaces = res;
	res = ft_strjoin(leading_spaces, res);
	free(ending_spaces);
	return (res);
}

char	*normalize_value(char *value)
{
	char	*leading_spaces;
	char	*ending_spaces;
	int		i;

	if (!value)
		return (NULL);
	i = 0;
	while (value[i] && ft_isspace(value[i]))
		i++;
	leading_spaces = ft_substr(value, 0, i);
	if (value[i])
	{
		i = ft_strlen(value) - 1;
		while (i >= 0 && ft_isspace(value[i]))
			i--;
		ending_spaces = ft_substr(value, i + 1, ft_strlen(value));
	}
	else
		ending_spaces = ft_strdup("");
	return (normalize_helper(value, leading_spaces, ending_spaces));
}
	*/