/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:39:02 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 17:37:59 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_error_and_code(const char *cmd, const char *msg, int code)
{
	ft_dprintf(2, "minishell: %s: %s\n", cmd, msg);
	g_cmd_error_code = code;
}

int	count_colons(const char *env_path)
{
	int			count;
	const char	*p;

	count = 1;
	p = env_path;
	while (*p)
	{
		if (*p == ':')
			count++;
		p++;
	}
	return (count);
}

char	**split_path(const char *env_path)
{
	int		count;
	char	**dirs;

	if (!env_path || !*env_path)
		return (NULL);
	count = count_colons(env_path);
	dirs = allocate_dirs(count);
	if (!dirs)
		return (NULL);
	if (!populate_dirs(env_path, dirs, count))
	{
		free_dirs(dirs);
		return (NULL);
	}
	return (dirs);
}

char	*handle_path(const char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) == 0)
	{
		if (is_valid_path(cmd, &st, cmd) == 1)
			return (ft_strdup(cmd));
		return (NULL);
	}
	set_error_and_code(cmd, "No such file or directory", 127);
	return (NULL);
}

char	*handle_missing_command(const char *cmd)
{
	set_error_and_code(cmd, "command not found", 127);
	return (NULL);
}
