/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:53:18 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/03 16:35:59 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_process(t_exec_context *ctx)
{
	reset_signals();
	if (duplicate_fds(ctx) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close_all_pipes(ctx);
	if (setup_redirections(ctx->cmd) == -1)
		exit(1);
	execute_command(ctx);
}

pid_t	fork_and_execute(t_exec_context *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child_process(ctx);
	else if (pid < 0)
		perror("fork");
	return (pid);
}

void	wait_child(int *last_exit_code, int status)
{
	if (WIFEXITED(status))
		*last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*last_exit_code = 128 + WTERMSIG(status);
	else
		*last_exit_code = 1;
}

void	wait_for_children(int cmd_count, pid_t *pids, int *last_exit_code)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		while (1)
		{
			if (waitpid(pids[i], &status, 0) == -1)
			{
				if (errno == EINTR)
					continue ;
				else
				{
					perror("waitpid");
					break ;
				}
			}
			break ;
		}
		if (i == cmd_count - 1)
			wait_child(last_exit_code, status);
		i++;
	}
}

pid_t	*c(int c_c, t_command *cmd, int (*pipes)[2], t_exec_params *par)
{
	int						i;
	pid_t					*pids;
	t_exec_context_params	ctx_params;

	pids = malloc(sizeof(pid_t) * c_c);
	if (!pids)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (i < c_c)
	{
		ctx_params.cmd = cmd;
		ctx_params.idx = i;
		ctx_params.cmd_count = c_c;
		ctx_params.pipes = pipes;
		ctx_params.params = par;
		pids[i] = e(&ctx_params);
		if (pids[i] < 0)
			return (free(pids), NULL);
		cmd = cmd->next;
		i++;
	}
	return (pids);
}
