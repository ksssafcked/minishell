/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:14:02 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:22:29 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_next_pipe(char **tokens)
{
	int	i;

	if (!tokens)
		return (NULL);
	if (!*tokens)
		return (free(tokens), NULL);
	i = 0;
	if (!ft_strcmp(tokens[i], "|"))
		i++;
	while (tokens[i] && ft_strcmp(tokens[i], "|"))
		i++;
	if (!tokens[i])
		tokens = free_all(tokens);
	else
		tokens = copy_tokens(tokens, i + 1);
	return (tokens);
}

char	*read_input_line(void)
{
	char	*line;

	line = readline("minishell> ");
	if (line && *line)
		add_history(line);
	return (line);
}

t_pipeline	*parse_pipeline_step(char **t, t_shell *s, char *line)
{
	t_pipeline	*pl;

	pl = parse_pipeline_loop(t, s);
	if (!pl)
	{
		free(line);
		return (NULL);
	}
	return (pl);
}

char	*read_input_and_exit(void)
{
	char	*line;

	line = read_input_line();
	if (line == NULL)
	{
		dprintf(1, "exit\n");
	}
	return (line);
}
