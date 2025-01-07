/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:46:20 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:46:57 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_input(t_command **cmd, int *index, char **tokens)
{
	if (!tokens[*index])
		return (0);
	if (!open_and_close_infile(tokens[*index]))
		return (0);
	return (set_input_file(*cmd, tokens[*index]));
}

int	handle_heredoc(t_command **cmd, int *index, char **tokens)
{
	if (!tokens[*index])
		return (0);
	return (set_heredoc(*cmd, tokens[*index]));
}
