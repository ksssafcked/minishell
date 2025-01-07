/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quote_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:41:52 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:46:43 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_simple_quote(const char *str)
{
	if (!str)
		return (0);
	return (str[0] == TOKEN_SINGLE_QUOTE);
}

int	is_double_quote(const char *str)
{
	if (!str)
		return (0);
	return (str[0] == TOKEN_DOUBLE_QUOTE);
}

void	update_quote_states(char c, int *in_sq, int *in_dq)
{
	if (c == '\'' && *in_dq == 0)
	{
		*in_sq = !*in_sq;
	}
	else if (c == '"' && *in_sq == 0)
	{
		*in_dq = !*in_dq;
	}
}
