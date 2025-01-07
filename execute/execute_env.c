/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:58:01 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 17:58:44 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_command_path_or_exit(t_env *env, char *cmd)
{
	char	*path;

	path = get_command_path(env, cmd);
	if (!path)
	{
		if (g_cmd_error_code != 0)
			exit(g_cmd_error_code);
		else
			exit(127);
	}
	return (path);
}

char	**prepare_envp(t_env *env)
{
	char	**envp_for_exec;

	envp_for_exec = env_to_char_array(env);
	if (!envp_for_exec)
	{
		perror("env_to_char_array");
		return (NULL);
	}
	return (envp_for_exec);
}

void	execute_builtin(t_shell *shell, char **argv)
{
	run_builtin(shell, argv);
}

void	execute_external(t_env *env, char **argv, char *pat, char **e_ex)
{
	int	k;

	(void)env;
	execve(pat, argv, e_ex);
	perror("execve");
	k = 0;
	while (e_ex[k])
	{
		free(e_ex[k]);
		k++;
	}
	free(e_ex);
	free(pat);
	exit(1);
}
