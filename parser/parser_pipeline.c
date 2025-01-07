/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:22:45 by qudomino          #+#    #+#             */
/*   Updated: 2024/12/29 19:48:35 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	allocate_pipeline(t_pipeline **pipeline)
{
	*pipeline = malloc(sizeof(t_pipeline));
	if (*pipeline == NULL)
		return (0);
	(*pipeline)->commands = NULL;
	return (1);
}

int	allocate_initial_command(t_pipeline *pipeline, t_command **cmd)
{
	*cmd = allocate_command();
	if (*cmd == NULL)
	{
		free(pipeline);
		return (0);
	}
	pipeline->commands = *cmd;
	return (1);
}

int	process_tokens_loop(t_pipeline *pipeline, t_command **cmd, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (!pst(pipeline, cmd, tokens, &i))
		{
			free_pipeline(pipeline);
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_pipeline(char **tokens, t_pipeline **pip)
{
	t_pipeline	*pipeline;
	t_command	*current_cmd;

	if (!allocate_pipeline(&pipeline))
	{
		*pip = NULL;
		return (0);
	}
	if (!allocate_initial_command(pipeline, &current_cmd))
	{
		*pip = NULL;
		return (0);
	}
	if (!process_tokens_loop(pipeline, &current_cmd, tokens))
	{
		*pip = NULL;
		return (-1);
	}
	*pip = pipeline;
	return (1);
}
