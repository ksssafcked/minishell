/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:06:40 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/03 17:07:14 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_pipe(int *fd)
{
	if (pipe(fd) == -1)
		return (-1);
	return (0);
}

int	c_heredoc_pipe_core(int fd_write, t_heredoc_info *info)
{
	int	result;

	result = process_iteration(fd_write, info);
	return (result);
}

void	i(t_heredoc_info *i, char *d, int h_q, t_expand_context *c)
{
	i->h_q = h_q;
	i->delim = d;
	i->context = c;
	i->line_count = 0;
	i->delim_found = 0;
}

int	handle_heredoc_loop(int fd_write, t_heredoc_info *info)
{
	int	result;

	while (1)
	{
		result = c_heredoc_pipe_core(fd_write, info);
		if (result == 1)
		{
			info->delim_found = 1;
			break ;
		}
		else if (result == 2)
			break ;
		else if (result == -1)
			return (-1);
	}
	return (result);
}
