/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_process_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:40:34 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:41:11 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_unquoted(const char *line, char *new_line, t_indices *idx)
{
	int	result;

	result = handle_char(line, new_line, idx->i, &idx->j);
	if (result < 0)
		return (0);
	idx->i = result;
	return (1);
}

int	process_unquoted(const char *line, char *new_line, t_indices *idx)
{
	if (!handle_unquoted(line, new_line, idx))
		return (0);
	return (1);
}

int	process_quoted(char c, char *new_line, t_indices *idx)
{
	new_line[idx->j] = c;
	idx->j++;
	return (1);
}

char	*allocate_initial_token(size_t capacity)
{
	char	*token;

	token = malloc(capacity + 1);
	if (token == NULL)
		return (NULL);
	token[0] = TOKEN_UNQUOTED;
	return (token);
}

char	*allocate_new_line(size_t len)
{
	char	*new_line;

	new_line = malloc(len * 4 + 1);
	if (new_line == NULL)
		return (NULL);
	return (new_line);
}
