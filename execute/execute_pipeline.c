/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:27:25 by qudomino          #+#    #+#             */
/*   Updated: 2024/12/29 19:05:04 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_command(t_exec_context *ctx)
{
	char	*path;
	char	**envp_for_exec;

	if (is_builtin_cmd(ctx->cmd->argv))
	{
		execute_builtin(ctx->shell, ctx->cmd->argv);
		exit(0);
	}
	else
	{
		path = get_command_path_or_exit(ctx->env, ctx->cmd->argv[0]);
		envp_for_exec = prepare_envp(ctx->env);
		if (!envp_for_exec)
		{
			free(path);
			exit(1);
		}
		execute_external(ctx->env, ctx->cmd->argv, path, envp_for_exec);
	}
}

t_exec_context	init_exec_context(t_exec_context_params *ctx_params)
{
	t_exec_context	ctx;

	ctx.cmd = ctx_params->cmd;
	ctx.idx = ctx_params->idx;
	ctx.cmd_count = ctx_params->cmd_count;
	ctx.pipes = ctx_params->pipes;
	ctx.env = ctx_params->params->env;
	ctx.shell = ctx_params->params->shell;
	return (ctx);
}

pid_t	e(t_exec_context_params *ctx_params)
{
	t_exec_context	ctx;

	ctx = init_exec_context(ctx_params);
	return (fork_and_execute(&ctx));
}

void	init_exec_params(t_exec_params *params, t_env *env, t_shell *shell)
{
	params->env = env;
	params->shell = shell;
}

int	execute_pipeline(t_pipeline *pipeline, t_env *env, t_shell *shell)
{
	int				cmd_count;
	int				last_exit_code;
	pid_t			*pids;
	t_exec_params	params;
	int				(*pipes)[2];

	pipes = NULL;
	init_exec_params(&params, env, shell);
	cmd_count = count_commands(pipeline->commands);
	if (cmd_count == 0)
		return (0);
	if (initialize_pipes(cmd_count, &pipes) == -1)
		return (1);
	pids = c(cmd_count, pipeline->commands, pipes, &params);
	if (!pids)
		return (handle_pids_error(cmd_count, pipes));
	last_exit_code = close_pipes_and_wait(cmd_count, pipes, pids);
	return (last_exit_code);
}
