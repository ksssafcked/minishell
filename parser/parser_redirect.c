/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:19:00 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:46:56 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_and_close_infile(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		handle_error_file(filename);
		g_cmd_error_code = 1;
		return (0);
	}
	close(fd);
	return (1);
}

int	open_and_close_file(const char *filename, int append)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		handle_error_file(filename);
		g_cmd_error_code = 1;
		return (0);
	}
	close(fd);
	return (1);
}

int	handle_output(t_command **cmd, int *index, char **tokens, int append)
{
	if (!tokens[*index])
		return (0);
	if (!open_and_close_file(tokens[*index], append))
		return (0);
	return (set_output_file(*cmd, tokens[*index], append));
}

int	hstok(t_command **cmd, char *token, int *index, char **tokens)
{
	(*index)++;
	if (ft_strcmp(token, "<") == 0)
	{
		return (handle_input(cmd, index, tokens));
	}
	if (ft_strcmp(token, "<<") == 0)
	{
		return (handle_heredoc(cmd, index, tokens));
	}
	if (ft_strcmp(token, ">") == 0)
	{
		return (handle_output(cmd, index, tokens, 0));
	}
	if (ft_strcmp(token, ">>") == 0)
	{
		return (handle_output(cmd, index, tokens, 1));
	}
	return (0);
}

int	pst(t_pipeline *pipe, t_command **cmd, char **tokens, int *index)
{
	char	*token;

	token = tokens[*index];
	if (ft_strcmp(token, "|") == 0)
	{
		*cmd = create_new_command(pipe);
		return (*cmd != NULL);
	}
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0
		|| ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0)
		return (hstok(cmd, token, index, tokens));
	return (extend_arguments(*cmd, token));
}
