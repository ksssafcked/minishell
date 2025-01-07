/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:15:24 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/03 16:17:24 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*add_direct(const char *s1, const char *s2)
{
	size_t	total_len;
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	total_len = get_len(s1, s2);
	str = (char *)malloc((total_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	if (str[i - 1] != '/')
		str[i++] = '/';
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*delete_this_dir(char *dir, int index, int len)
{
	int		j;
	char	*new_dir;

	j = index + len;
	while (dir[j])
	{
		dir[index] = dir[j];
		j++;
		index++;
	}
	dir[index] = '\0';
	new_dir = ft_strdup(dir);
	free(dir);
	return (new_dir);
}

char	*delete_last_dir(char *directory, int index)
{
	int		j;
	int		k;
	char	*new_dir;

	if (!index)
	{
		directory[1] = '\0';
		new_dir = ft_strdup(directory);
		free(directory);
		return (new_dir);
	}
	j = index - 1;
	while (j >= 0 && directory[j] != '/')
		j--;
	k = index + 3;
	new_dir = delete_this_dir(directory, j, k - j);
	return (new_dir);
}

char	*parse_dir(char *dir)
{
	int	i;

	i = 0;
	while (dir && dir[i])
	{
		if (!ft_strncmp(&dir[i], "/../", 4) || !ft_strcmp(&dir[i], "/.."))
			dir = delete_last_dir(dir, i);
		else if (!ft_strncmp(&dir[i], "/./", 3) || !ft_strcmp(&dir[i], "/."))
			dir = delete_this_dir(dir, i, 2);
		else
		{
			i++;
			continue ;
		}
		i = 0;
	}
	if (!dir)
		return (NULL);
	if (!ft_strlen(dir))
	{
		free(dir);
		dir = ft_strdup("/");
	}
	return (dir);
}

char	*parse_new_dir(t_shell *shell, char **args)
{
	char	*new_dir;
	char	*actual;

	actual = ft_strdup(shell->directory);
	if (args[1][0] != '/')
	{
		new_dir = add_direct(actual, args[1]);
		free(actual);
	}
	else
	{
		new_dir = ft_strdup(args[1]);
		free(actual);
	}
	new_dir = parse_dir(new_dir);
	return (new_dir);
}
