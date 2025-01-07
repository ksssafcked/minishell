/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pp_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:47:58 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:48:32 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_input_file(t_command *cmd, char *token)
{
	cmd->infile = ft_strdup(token);
	return (cmd->infile != NULL);
}

int	set_output_file(t_command *cmd, char *token, int append)
{
	cmd->outfile = ft_strdup(token);
	if (!cmd->outfile)
		return (0);
	cmd->append = append;
	return (1);
}

int	set_heredoc(t_command *cmd, char *token)
{
	cmd->heredoc_delim = ft_strdup(token);
	return (cmd->heredoc_delim != NULL);
}
