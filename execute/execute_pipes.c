/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:55:13 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:04:58 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	duplicate_fds(t_exec_context *ctx)
{
	if (ctx->idx > 0)
	{
		if (dup2(ctx->pipes[ctx->idx - 1][0], STDIN_FILENO) == -1)
			return (-1);
	}
	if (ctx->idx < ctx->cmd_count - 1)
	{
		if (dup2(ctx->pipes[ctx->idx][1], STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

void	close_all_pipes(t_exec_context *ctx)
{
	int	j;

	j = 0;
	while (j < ctx->cmd_count -1)
	{
		close(ctx->pipes[j][0]);
		close(ctx->pipes[j][1]);
		j++;
	}
}

int	initialize_pipes(int cmd_count, int (**pipes)[2])
{
	if (cmd_count > 1)
	{
		*pipes = malloc(sizeof(int [2]) * (cmd_count - 1));
		if (!*pipes)
		{
			perror("malloc");
			return (-1);
		}
		if (setup_pipes(cmd_count, *pipes) == -1)
			return (-1);
	}
	return (0);
}

int	handle_pids_error(int cmd_count, int (*pipes)[2])
{
	if (pipes)
		close_pipes(cmd_count, pipes);
	return (1);
}

int	close_pipes_and_wait(int cmd_count, int (*pipes)[2], pid_t *pids)
{
	int	last_exit_code;

	last_exit_code = 0;
	if (pipes)
		close_pipes(cmd_count, pipes);
	wait_for_children(cmd_count, pids, &last_exit_code);
	free(pids);
	return (last_exit_code);
}
