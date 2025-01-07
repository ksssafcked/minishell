/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:25:51 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/03 17:02:36 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	initialize_shell(t_shell *shell, char **envp)
{
	shell->env = env_init(envp);
	if (!shell->env)
		return (0);
	shell->directory = getcwd(NULL, 0);
	if (!shell->directory)
	{
		shell->should_exit = 1;
		return (0);
	}
	shell->last_exit_code = 0;
	shell->should_exit = 0;
	init_signals();
	return (1);
}

t_pipeline	*parse_pipeline_loop(char **tokens, t_shell *shell)
{
	t_pipeline	*pl;
	int			par_return;

	pl = NULL;
	while (tokens)
	{
		par_return = parse_pipeline(tokens, &pl);
		if (!handle_parse_result(par_return, tokens, shell))
			return (NULL);
		if (par_return == -1)
		{
			tokens = handle_par_return_neg_one(tokens, shell);
			if (tokens == NULL)
				return (NULL);
		}
		else
		{
			free_tokens(tokens);
			break ;
		}
	}
	return (pl);
}

void	execute_commands(t_pipeline *pl, t_shell *shell)
{
	int	ret;

	if (is_single_command_no_pipe(pl))
	{
		ret = execute_pipeline(pl, shell->env, shell);
		shell->last_exit_code = ret;
	}
	else
	{
		ret = execute_pipeline(pl, shell->env, shell);
		shell->last_exit_code = ret;
	}
	free_pipeline(pl);
}

void	shell_loop(t_shell *shell)
{
	int	continue_loop;

	continue_loop = 1;
	while (continue_loop)
	{
		continue_loop = process_iterations(shell);
	}
}
