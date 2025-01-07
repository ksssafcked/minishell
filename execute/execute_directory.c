/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_directory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:31:46 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 17:37:54 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_dirs(char **dirs)
{
	int	j;

	j = 0;
	while (dirs[j])
	{
		free(dirs[j]);
		j++;
	}
	free(dirs);
}

char	**allocate_dirs(int count)
{
	return (malloc(sizeof(char *) * (count + 1)));
}

char	*allocate_and_copy_dir(const char *env_path, int start, int end)
{
	int		length;
	char	*dir;

	length = end - start;
	dir = malloc(length + 1);
	if (!dir)
		return (NULL);
	ft_strncpy(dir, env_path + start, length);
	dir[length] = '\0';
	return (dir);
}

int	populate_dirs(const char *env_path, char **dirs, int count)
{
	int	i;
	int	start;
	int	c;
	int	len;

	i = 0;
	start = 0;
	c = 0;
	len = ft_strlen(env_path);
	count = 0;
	while (c <= len)
	{
		if (env_path[c] == ':' || env_path[c] == '\0')
		{
			dirs[i] = allocate_and_copy_dir(env_path, start, c);
			if (!dirs[i])
				return (0);
			i++;
			start = c + 1;
		}
		c++;
	}
	dirs[i] = NULL;
	return (1);
}

char	*search_directories(char **dirs, const char *cmd, struct stat *st)
{
	int		i;
	int		valid;
	char	*full;

	i = 0;
	while (dirs[i])
	{
		full = construct_full_path(dirs[i], cmd);
		if (!full)
			break ;
		valid = is_valid_path(full, st, cmd);
		if (valid == 1)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}
