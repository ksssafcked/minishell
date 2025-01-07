/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:02:27 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:42:23 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_quotes(char c, t_parser_context *ctx)
{
	if (c == '\'' && !ctx->in_double_quote)
	{
		if (ctx->in_single_quote)
			ctx->in_single_quote = 0;
		else
		{
			ctx->in_single_quote = 1;
			ctx->token[0] = TOKEN_SINGLE_QUOTE;
		}
		*(ctx->line_ptr) += 1;
		return (1);
	}
	if (c == '"' && !ctx->in_single_quote)
	{
		if (ctx->in_double_quote)
			ctx->in_double_quote = 0;
		else
		{
			ctx->in_double_quote = 1;
			ctx->token[0] = TOKEN_DOUBLE_QUOTE;
		}
		*(ctx->line_ptr) += 1;
		return (1);
	}
	return (0);
}

int	handle_special_char(const char *line, char *new_line, size_t i, size_t *j)
{
	if (!line || !new_line || !j)
		return (i);
	i = h_spe_char(line, new_line, i, j);
	return (i);
}

void	copy_regular_char(const char *line, char *new_line, size_t i, size_t *j)
{
	if (!line || !new_line || !j)
		return ;
	new_line[*j] = line[i];
	(*j)++;
}

int	handle_char(const char *line, char *new_line, size_t i, size_t *j)
{
	if (!line || !new_line || !j)
		return (i);
	if (is_special_char(line[i]))
	{
		i = handle_special_char(line, new_line, i, j);
		return (i);
	}
	copy_regular_char(line, new_line, i, j);
	return (i);
}
