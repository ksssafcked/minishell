/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:54:19 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/03 16:26:16 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_line_core(int fd_write, char *line, t_heredoc_info *info)
{
	ssize_t	len;

	len = ft_strlen(line);
	if (len > 0)
	{
		if (line[len - 1] == '\n')
		{
			line[len - 1] = '\0';
		}
	}
	if (ft_strcmp(line, info->delim) == 0)
		return (1);
	if (w_to_p(fd_write, line, info->h_q, info->context) == -1)
		return (-1);
	return (0);
}

int	process_line(int fd_write, char *line, t_heredoc_info *info)
{
	ssize_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (ft_strcmp(line, info->delim) == 0)
		return (1);
	if (w_to_p(fd_write, line, info->h_q, info->context) == -1)
		return (-1);
	return (0);
}

int	process_iteration(int fd_write, t_heredoc_info *info)
{
	char	*line;
	int		result;

	info->line_count++;
	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	if (!line)
	{
		return (2);
	}
	result = process_line(fd_write, line, info);
	free(line);
	return (result);
}

int	process_heredocs(t_command *cmds, t_env *env, int last_exit_code)
{
	t_command			*c;
	int					success;
	t_expand_context	context;

	context.env = env;
	context.last_exit_code = last_exit_code;
	c = cmds;
	success = 1;
	while (c)
	{
		if (c->heredoc_delim)
		{
			if (!handle_single_heredoc(c, &context))
			{
				success = 0;
				break ;
			}
		}
		c = c->next;
	}
	return (success);
}
