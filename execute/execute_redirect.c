/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:51:18 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 17:51:44 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	configure_output_flags(t_command *cmd, int *flags)
{
	*flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		*flags |= O_APPEND;
	else
		*flags |= O_TRUNC;
	return (0);
}

int	open_output_file(t_command *cmd, int flags)
{
	int	out_fd;

	out_fd = open(cmd->outfile, flags, 0644);
	if (out_fd < 0)
	{
		handle_error_file(cmd->outfile);
		return (-1);
	}
	return (out_fd);
}

int	dup_output_fd(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_output_redirection(t_command *cmd)
{
	int	flags;
	int	out_fd;

	if (cmd->out_fd != -1)
	{
		if (dup2(cmd->out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (-1);
		}
		close(cmd->out_fd);
	}
	else if (cmd->outfile)
	{
		configure_output_flags(cmd, &flags);
		out_fd = open_output_file(cmd, flags);
		if (out_fd == -1)
			return (-1);
		if (dup_output_fd(out_fd) == -1)
			return (-1);
	}
	return (0);
}

int	setup_redirections(t_command *cmd)
{
	if (setup_input_redirection(cmd) == -1)
		return (-1);
	if (setup_output_redirection(cmd) == -1)
		return (-1);
	return (0);
}
