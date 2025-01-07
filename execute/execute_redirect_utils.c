/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:52:15 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 17:52:41 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_pipes(int cmd_count, int (*pipes)[2])
{
	int	j;

	j = 0;
	while (j < cmd_count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	free(pipes);
}

int	setup_pipes(int cmd_count, int (*pipes)[2])
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			j = 0;
			while (j < i)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			free(pipes);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	open_input_file(t_command *cmd)
{
	int	in_fd;

	in_fd = open(cmd->infile, O_RDONLY);
	if (in_fd < 0)
	{
		handle_error_file(cmd->infile);
		return (-1);
	}
	return (in_fd);
}

int	dup_input_fd(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_input_redirection(t_command *cmd)
{
	int	in_fd;

	if (cmd->in_fd != -1)
	{
		if (dup2(cmd->in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (-1);
		}
		close(cmd->in_fd);
	}
	else if (cmd->infile)
	{
		in_fd = open_input_file(cmd);
		if (in_fd == -1)
			return (-1);
		if (dup_input_fd(in_fd) == -1)
			return (-1);
	}
	return (0);
}
