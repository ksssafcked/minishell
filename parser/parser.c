/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:11:08 by qudomino          #+#    #+#             */
/*   Updated: 2024/12/29 17:38:47 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_space_if_needed(char *new_line, size_t *j)
{
	if (*j > 0 && new_line[*j - 1] != ' ')
	{
		new_line[*j] = ' ';
		(*j)++;
	}
}

void	add_special_char(char *new_line, char c, size_t *j)
{
	new_line[*j] = c;
	(*j)++;
}

int	is_double_operator(const char *line, size_t i)
{
	if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>'
			&& line[i + 1] == '>'))
	{
		return (1);
	}
	return (0);
}

void	hand_t_s(const char *line, char *new_line, size_t i, size_t *j)
{
	if (line[i + 1] && !is_whitespace(line[i + 1]))
	{
		new_line[*j] = ' ';
		(*j)++;
	}
}

size_t	h_spe_char(const char *l, char *n_l, size_t i, size_t *j)
{
	char	c;
	int		double_op;

	c = l[i];
	double_op = is_double_operator(l, i);
	add_space_if_needed(n_l, j);
	add_special_char(n_l, c, j);
	if (double_op)
	{
		i++;
		add_special_char(n_l, c, j);
	}
	hand_t_s(l, n_l, i, j);
	return (i);
}
