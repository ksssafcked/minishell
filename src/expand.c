/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:19:59 by qudomino          #+#    #+#             */
/*   Updated: 2024/12/29 20:03:59 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*handle_backslash(char *result, const char *token,
		t_expand_con *context)
{
	(*(context->i))++;
	if (token[*(context->i)] == '$')
	{
		return (handle_backslash_dollar(result, token, context));
	}
	else if (token[*(context->i)] == '\\')
	{
		return (handle_backslash_backslash(result, token, context));
	}
	else
	{
		return (handle_backslash_other(result, token, context));
	}
}

char	*handle_dollar_case(char *result, const char *token,
		t_expand_con *context)
{
	return (process_dollar(result, token, context));
}

char	*handle_default(char *result, const char *token, t_expand_con *context)
{
	char	c;

	c = token[*(context->i)];
	(*(context->i))++;
	return (append_char(result, c));
}

char	*handle_char_sec(char *result, const char *token, t_expand_con *context)
{
	if (token[*(context->i)] == '\\')
	{
		return (handle_backslash(result, token, context));
	}
	else if (token[*(context->i)] == '$')
	{
		(*(context->i))++;
		return (handle_dollar_case(result, token, context));
	}
	else
	{
		return (handle_default(result, token, context));
	}
}

char	*expand_token(const char *token, t_env *env, int last_exit_code)
{
	t_expand_con	context;
	char			*result;
	int				i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	context.last_exit_code = last_exit_code;
	context.i = &i;
	context.env = env;
	while (token && token[i])
	{
		result = handle_char_sec(result, token, &context);
		if (!result)
			return (NULL);
	}
	return (result);
}
