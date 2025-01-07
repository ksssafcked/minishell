/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:26:39 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:27:00 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_operator_token(char *s)
{
	if (!s)
		return (0);
	if (s[0] != TOKEN_UNQUOTED && s[0] != TOKEN_SINGLE_QUOTE
		&& s[0] != TOKEN_DOUBLE_QUOTE)
		return (0);
	s++;
	if (!ft_strcmp(s, "|") || !ft_strcmp(s, "<") || !ft_strcmp(s, ">")
		|| !ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"))
		return (1);
	return (0);
}

int	is_single_command_no_pipe(t_pipeline *pl)
{
	if (!pl || !pl->commands)
		return (0);
	return (pl->commands->next == NULL);
}

void	execute_builtin_command(t_shell *shell, char **argv)
{
	run_builtin(shell, argv);
}

void	cleanup(t_pipeline *pl, char *line)
{
	free_pipeline(pl);
	free(line);
}
