/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:14:11 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/03 16:17:28 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_len(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
		i++;
	if (s1[i - 1] != '/')
		i++;
	j = 0;
	while (s2[j])
		j++;
	return (i + j);
}

int	change_dir(t_shell *shell, char *directory, char *arg)
{
	if (!directory)
		return (1);
	if (chdir(directory) != 0)
	{
		ft_dprintf(2, "minishell: cd: %s: ", arg);
		perror("");
		free(directory);
		return (1);
	}
	free(shell->directory);
	shell->directory = directory;
	change_pwd(shell->env, directory);
	return (0);
}

int	cd_cmd(t_shell *shell, t_env *env, char **args)
{
	char	*dir;
	char	*home;

	home = env_get_value(env, "HOME");
	if (args[1] && args[2])
		return (ft_dprintf(2, "minishell: cd: too many arguments\n"), 1);
	if (!args[1] || !ft_strncmp(args[1], "~", 2) || !ft_strlen(args[1]))
	{
		if (!home)
			return (ft_dprintf(2, "minishell: cd: HOME not set\n"), 1);
		dir = ft_strdup(home);
	}
	else
		dir = parse_new_dir(shell, args);
	return (change_dir(shell, dir, args[1]));
}
