/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:24:07 by qudomino          #+#    #+#             */
/*   Updated: 2025/01/03 17:06:59 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	c_heredoc_pipe(char *delim, int h_q, t_expand_context *context)
{
	int				fd[2];
	t_heredoc_info	info;
	int				result;

	if (init_pipe(fd) == -1)
		return (-1);
	i(&info, delim, h_q, context);
	result = handle_heredoc_loop(fd[1], &info);
	close(fd[1]);
	if (result == -1)
	{
		close(fd[0]);
		return (-1);
	}
	if (result == 2 && !info.delim_found)
		dprintf(2, "bash: warning: here-document at line %d "
			"delimited by end-of-file (wanted '%s')\n",
			info.line_count, info.delim);
	return (fd[0]);
}

int	handle_heredoc_quoted(t_command *cmd)
{
	char	*clean_delim;

	clean_delim = remove_quotes(cmd->heredoc_delim);
	if (!clean_delim)
		return (0);
	free(cmd->heredoc_delim);
	cmd->heredoc_delim = clean_delim;
	return (1);
}

int	handle_single_heredoc(t_command *cmd, t_expand_context *context)
{
	int	heredoc_quoted;
	int	in_fd;

	heredoc_quoted = is_heredoc_quoted(cmd->heredoc_delim);
	if (heredoc_quoted)
	{
		if (!handle_heredoc_quoted(cmd))
			return (0);
	}
	in_fd = c_heredoc_pipe(cmd->heredoc_delim, heredoc_quoted, context);
	if (in_fd == -1)
		return (0);
	cmd->infile = NULL;
	cmd->append = 0;
	cmd->in_fd = in_fd;
	return (1);
}
