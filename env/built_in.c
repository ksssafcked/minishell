/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:52:12 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/03 16:31:48 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_nl_arg(char *args)
{
	if (*args != '-')
		return (0);
	args++;
	if (*args != 'n')
		return (0);
	while (*args)
	{
		if (*args != 'n')
			return (0);
		args++;
	}
	return (1);
}

bool	process_argument(t_env *env, char *arg, int *exit_code)
{
	if (!is_valid_identifier(arg))
	{
		ft_dprintf(2, "export: `%s': not a valid identifier\n", arg);
		*exit_code = 1;
		return (false);
	}
	if (has_value(arg))
		set_env_var(env, arg);
	else
	{
		if (arg[0])
			set_env_no_value(env, arg);
	}
	return (true);
}

int	handle_echo(t_shell *shell, char **args)
{
	echo_cmd(args);
	shell->last_exit_code = 0;
	return (1);
}

int	handle_exit(t_shell *shell, char **args)
{
	int	ret;

	ret = exit_cmd(args, shell->last_exit_code, \
		&shell->should_exit, shell->env);
	shell->last_exit_code = ret;
	if (shell->should_exit)
		ft_dprintf(1, "exit\n");
	return (1);
}

int	run_builtin(t_shell *shell, char **args)
{
	if (!args || !args[0])
		return (0);
	if (ft_strcmp(args[0], "echo") == 0)
		return (handle_echo(shell, args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (handle_cd(shell, args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (handle_pwd(shell, args));
	if (ft_strcmp(args[0], "export") == 0)
		return (handle_export(shell, args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (handle_unset(shell, args));
	if (ft_strcmp(args[0], "env") == 0)
		return (handle_env(shell, args));
	if (ft_strcmp(args[0], "exit") == 0)
		return (handle_exit(shell, args));
	return (0);
}
