/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:58:39 by qudomino          #+#    #+#             */
/*   Updated: 2024/12/29 17:38:02 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_cmd_error_code = 0;

int	is_valid_path(const char *full, struct stat *st, const char *cmd)
{
	if (stat(full, st) != 0)
		return (0);
	if (S_ISDIR(st->st_mode))
	{
		set_error_and_code(cmd, "Is a directory", 126);
		return (-1);
	}
	if (access(full, X_OK) != 0)
	{
		if (errno == EACCES)
			set_error_and_code(cmd, "Permission denied", 126);
		else
			set_error_and_code(cmd, "No such file or directory", 127);
		return (-1);
	}
	return (1);
}

char	*construct_full_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	if (!dir)
		return (NULL);
	tmp = ft_strdup(dir);
	if (!tmp)
		return (NULL);
	full = malloc(ft_strlen(tmp) + ft_strlen(cmd) + 2);
	if (!full)
	{
		free(tmp);
		return (NULL);
	}
	ft_strcpy(full, tmp);
	ft_strcat(full, "/");
	ft_strcat(full, cmd);
	free(tmp);
	return (full);
}

char	*get_command_path(t_env *env, const char *cmd)
{
	struct stat	st;
	char		*env_path;
	char		**dirs;
	char		*result;

	g_cmd_error_code = 0;
	if (!cmd || !*cmd)
		return (handle_missing_command(cmd));
	if (ft_strchr(cmd, '/'))
		return (handle_path(cmd));
	env_path = env_get_value(env, "PATH");
	dirs = split_path(env_path);
	if (dirs == NULL)
		return (handle_missing_command(cmd));
	result = search_directories(dirs, cmd, &st);
	free_dirs(dirs);
	if (result != NULL)
		return (result);
	else
		return (handle_missing_command(cmd));
}
