/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:23:58 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:24:20 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_redirections(t_pipeline *pl, t_shell *shell, char *line)
{
	t_command	*cmd;

	cmd = pl->commands;
	if (is_single_command_no_pipe(pl) && (!cmd->argv || cmd->argv[0] == NULL))
	{
		if (!open_all_redirections(pl, &shell->last_exit_code))
			return (0);
		if (cmd->in_fd != -1)
			close(cmd->in_fd);
		free_pipeline(pl);
		free(line);
		shell->last_exit_code = 1;
		return (1);
	}
	return (2);
}

int	save_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
		return (0);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		close(*saved_stdin);
		return (0);
	}
	return (1);
}

int	redirect_fds(t_command *c)
{
	if (c->in_fd != -1)
	{
		if (dup2(c->in_fd, STDIN_FILENO) == -1)
			return (0);
		close(c->in_fd);
	}
	if (c->out_fd != -1)
	{
		if (dup2(c->out_fd, STDOUT_FILENO) == -1)
			return (0);
		close(c->out_fd);
	}
	return (1);
}

int	restore_fds(int saved_stdin, int saved_stdout)
{
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		return (0);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		return (0);
	close(saved_stdin);
	close(saved_stdout);
	return (1);
}
