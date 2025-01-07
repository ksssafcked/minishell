/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:03:36 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:41:13 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	skip_spaces(const char **line)
{
	while (**line == ' ' || **line == '\t' || **line == '\n' || **line == '\r'
		|| **line == '\v' || **line == '\f')
	{
		(*line)++;
	}
}

int	process_character(const char *line, char *new_line, t_indices *idx,
		t_quote_state *state)
{
	if (!state->in_single_quote && !state->in_double_quote)
	{
		if (!process_unquoted(line, new_line, idx))
			return (0);
	}
	else
	{
		if (!process_quoted(line[idx->i], new_line, idx))
			return (0);
	}
	return (1);
}

void	update_q_states(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	if (c == '\"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

int	preprocess_loop(const char *line, char *new_line, size_t len)
{
	t_quote_state	state;
	t_indices		idx;
	int				result;

	state.in_single_quote = 0;
	state.in_double_quote = 0;
	idx.i = 0;
	idx.j = 0;
	while (idx.i < len)
	{
		update_q_states(line[idx.i], &state.in_single_quote,
			&state.in_double_quote);
		result = process_character(line, new_line, &idx, &state);
		if (!result)
			return (0);
		idx.i++;
	}
	new_line[idx.j] = '\0';
	if (state.in_single_quote || state.in_double_quote)
	{
		ft_dprintf(2, "minishell: syntax error: unclosed quote\n");
		free(new_line);
		return (0);
	}
	return (1);
}

char	*preprocess_line(const char *line)
{
	size_t	len;
	char	*new_line;

	len = ft_strlen(line);
	new_line = allocate_new_line(len);
	if (new_line == NULL)
		return (NULL);
	if (!preprocess_loop(line, new_line, len))
		return (NULL);
	return (new_line);
}
