/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:24:14 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 17:38:14 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**extend_argv(char **argv, int count)
{
	return (ft_realloc(argv, sizeof(char *) * (count + 2)));
}

t_command	*allocate_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->in_fd = -1;
	cmd->out_fd = -1;
	cmd->append = 0;
	cmd->heredoc_quoted = 0;
	cmd->next = NULL;
	return (cmd);
}

int	extend_arguments(t_command *cmd, char *token)
{
	int		count;
	char	**new_args;

	count = 0;
	while (cmd->argv && cmd->argv[count])
		count++;
	new_args = extend_argv(cmd->argv, count);
	if (!new_args)
		return (0);
	cmd->argv = new_args;
	cmd->argv[count] = ft_strdup(token);
	if (!cmd->argv[count])
		return (0);
	cmd->argv[count + 1] = NULL;
	return (1);
}

void	append_command_to_pipeline(t_pipeline *pipeline, t_command *cmd)
{
	t_command	*last;

	last = pipeline->commands;
	while (last->next)
		last = last->next;
	last->next = cmd;
}

t_command	*create_new_command(t_pipeline *pipeline)
{
	t_command	*cmd;

	cmd = allocate_command();
	if (!cmd)
		return (NULL);
	if (!pipeline->commands)
		pipeline->commands = cmd;
	else
		append_command_to_pipeline(pipeline, cmd);
	return (cmd);
}
