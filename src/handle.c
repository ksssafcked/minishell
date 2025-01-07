/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:24:58 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:25:31 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_ctrl_backslash(int count, int key)
{
	(void)count;
	(void)key;
	return (0);
}

void	handle_parse_error(char **tokens, t_shell *shell)
{
	free_tokens(tokens);
	shell->last_exit_code = 2;
}

char	**handle_par_return_neg_one(char **tokens, t_shell *shell)
{
	shell->last_exit_code = 1;
	tokens = get_next_pipe(tokens);
	if (tokens == NULL)
		shell->last_exit_code = 1;
	return (tokens);
}

int	handle_parse_result(int par_return, char **tokens, t_shell *shell)
{
	if (par_return == 0)
	{
		handle_parse_error(tokens, shell);
		return (0);
	}
	return (1);
}

int	handle_builtin(t_pipeline *pl, t_shell *shell, char *line)
{
	t_command	*c;
	int			saved_stdin;
	int			saved_stdout;

	if (!is_single_command_no_pipe(pl))
		return (2);
	if (!is_builtin_cmd(pl->commands->argv))
		return (2);
	if (!open_all_redirections(pl, &shell->last_exit_code))
		return (0);
	c = pl->commands;
	if (!save_fds(&saved_stdin, &saved_stdout))
		return (0);
	if (!redirect_fds(c))
	{
		restore_fds(saved_stdin, saved_stdout);
		return (0);
	}
	execute_builtin_command(shell, c->argv);
	if (!restore_fds(saved_stdin, saved_stdout))
		return (0);
	cleanup(pl, line);
	return (1);
}
