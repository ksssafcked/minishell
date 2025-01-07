/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:13:00 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/03 17:04:03 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_commands_step(t_pipeline *pl, t_shell *shell, char *line)
{
	execute_commands(pl, shell);
	if (shell->should_exit)
	{
		free(line);
		return (0);
	}
	free(line);
	return (1);
}

static int	handle_signal(t_shell *shell)
{
	if (g_received_signal)
	{
		shell->last_exit_code = 130;
		g_received_signal = 0;
		return (1);
	}
	return (0);
}

static int	validate_and_parse(t_process_vars *vars, t_shell *shell)
{
	vars->tokens = tokenize_input(vars->line);
	if (!vars->tokens)
		return (free(vars->line), 1);
	if (!validate_tokens(vars->tokens, shell, vars->line))
		return (1);
	vars->pl = parse_pipeline_step(vars->tokens, shell, vars->line);
	if (!vars->pl)
		return (1);
	return (0);
}

static int	handle_process_steps(t_process_vars *vars, t_shell *shell)
{
	vars->status = process_redirections_step(vars->pl, shell, vars->line);
	if (vars->status == 1 || vars->status == -1)
		return (1);
	vars->status = process_builtins_step(vars->pl, shell, vars->line);
	if (vars->status == 0)
		return (0);
	if (vars->status == 1)
		return (1);
	return (execute_commands_step(vars->pl, shell, vars->line));
}

int	process_iterations(t_shell *shell)
{
	t_process_vars	vars;

	vars.line = read_input_and_exit();
	if (!vars.line)
		return (0);
	if (handle_signal(shell))
		return (1);
	if (validate_and_parse(&vars, shell))
		return (1);
	return (handle_process_steps(&vars, shell));
}
