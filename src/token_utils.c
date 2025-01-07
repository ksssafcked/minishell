/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:22:50 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:23:33 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	validate_syntax(char **t, int count)
{
	int	i;

	i = 0;
	if (!ft_strcmp(t[0] + 1, "|"))
		return (0);
	while (i < count)
	{
		if (is_operator_token(t[i]))
		{
			if (i == count - 1)
				return (i);
			if (!ft_strcmp(t[i] + 1, "|") && !ft_strcmp(t[i + 1] + 1, "|"))
				return (i);
			if (ft_strcmp(t[i] + 1, "|") && is_operator_token(t[i + 1]))
				return (i + 1);
		}
		i++;
	}
	return (-1);
}

int	check_syntax(char **t, int count, t_shell *shell)
{
	int	s;

	s = validate_syntax(t, count);
	if (s != -1)
	{
		ft_dprintf(2, ": syntax error near unexpected token `%s'\n", t[s] + 1);
		free_tokens(t);
		shell->last_exit_code = 2;
		return (0);
	}
	return (1);
}

char	**copy_tokens(char **tokens, int start)
{
	int		i;
	char	**new_tokens;

	i = 0;
	while (tokens[start + i])
		i++;
	new_tokens = malloc(sizeof(char *) * (i + 1));
	if (!new_tokens)
		return (free_all(tokens));
	i = 0;
	while (tokens[start + i])
	{
		new_tokens[i] = tokens[start + i];
		i++;
	}
	new_tokens[i] = NULL;
	tokens[start] = NULL;
	free_all(tokens);
	return (new_tokens);
}

char	**tokenize_line(char *line)
{
	char	**tokens;

	tokens = ft_split_line(line);
	if (!tokens || !tokens[0])
	{
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}

int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}
