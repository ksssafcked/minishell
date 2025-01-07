/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:03:46 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/03 17:05:29 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_redirections_step(t_pipeline *pl, t_shell *s, char *line)
{
	int	redir_status;

	redir_status = handle_redirections(pl, s, line);
	if (redir_status == 1)
		return (1);
	if (redir_status == 0)
	{
		free_pipeline(pl);
		free(line);
		return (-1);
	}
	if (!process_heredocs(pl->commands, s->env, s->last_exit_code))
	{
		free_pipeline(pl);
		free(line);
		return (-1);
	}
	return (0);
}

int	process_builtins_step(t_pipeline *pl, t_shell *shell, char *line)
{
	int	builtin_status;

	builtin_status = handle_builtin(pl, shell, line);
	if (builtin_status == 1)
	{
		if (shell->should_exit)
			return (0);
		return (1);
	}
	if (builtin_status == 0)
	{
		free_pipeline(pl);
		free(line);
		return (-1);
	}
	return (2);
}
