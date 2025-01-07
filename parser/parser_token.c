/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:00:49 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 17:38:26 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*resize_token(char *token, size_t *capacity)
{
	char	*new_token;

	*capacity *= 2;
	new_token = ft_realloc(token, *capacity + 1);
	if (new_token == NULL)
	{
		free(token);
		return (NULL);
	}
	return (new_token);
}

char	*pl(t_parser_context *ctx)
{
	char	c;
	char	*resized;

	while (**ctx->line_ptr != '\0')
	{
		c = **ctx->line_ptr;
		if (!ctx->in_single_quote && !ctx->in_double_quote && is_whitespace(c))
			break ;
		if (handle_quotes(c, ctx))
			continue ;
		if (ctx->length + 1 >= ctx->capacity)
		{
			resized = resize_token(ctx->token, &ctx->capacity);
			if (resized == NULL)
				return (NULL);
			ctx->token = resized;
		}
		ctx->token[ctx->length] = c;
		ctx->length++;
		*(ctx->line_ptr) += 1;
	}
	ctx->token[ctx->length] = '\0';
	return (ctx->token);
}

char	*get_next_token(const char **line)
{
	t_parser_context	ctx;

	ctx.line_ptr = line;
	ctx.in_single_quote = 0;
	ctx.in_double_quote = 0;
	ctx.capacity = 128;
	ctx.length = 1;
	ctx.token = allocate_initial_token(ctx.capacity);
	if (ctx.token == NULL)
		return (NULL);
	if (pl(&ctx) == NULL)
	{
		free(ctx.token);
		return (NULL);
	}
	return (ctx.token);
}

char	**cleanup_tokens(char **tokens, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (NULL);
}

int	add_token(char ***tokens, size_t *count, char *token)
{
	char	**new_tokens;

	new_tokens = ft_realloc(*tokens, sizeof(char *) * (*count + 2));
	if (!new_tokens)
	{
		free(token);
		return (0);
	}
	*tokens = new_tokens;
	(*tokens)[*count] = token;
	(*count)++;
	(*tokens)[*count] = NULL;
	return (1);
}
