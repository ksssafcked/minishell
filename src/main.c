/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:32:33 by qudomino          #+#    #+#             */
/*   Updated: 2025/01/03 16:07:35 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	rl_bind_key(0x1C, handle_ctrl_backslash);
	if (!initialize_shell(&shell, envp))
	{
		ft_dprintf(2, "Error: failed to init env\n");
		return (1);
	}
	shell_loop(&shell);
	env_free(shell.env);
	free(shell.directory);
	return (shell.last_exit_code);
}
