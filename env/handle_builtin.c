/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:19:19 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/02 18:11:11 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_cd(t_shell *shell, char **args)
{
	shell->last_exit_code = cd_cmd(shell, shell->env, args);
	return (1);
}

int	handle_pwd(t_shell *shell, char **args)
{
	(void)shell;
	(void)args;
	pwd_cmd(shell);
	shell->last_exit_code = 0;
	return (1);
}

int	handle_export(t_shell *shell, char **args)
{
	export_cmd(shell, shell->env, args);
	return (1);
}

int	handle_unset(t_shell *shell, char **args)
{
	shell->env = unset_cmd(shell->env, args);
	shell->last_exit_code = 0;
	return (1);
}

int	handle_env(t_shell *shell, char **args)
{
	(void)args;
	env_cmd(shell->env);
	shell->last_exit_code = 0;
	return (1);
}
