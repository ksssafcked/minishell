/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:03:12 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 20:03:26 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*handle_dollar(char *result)
{
	char	*tmp;

	tmp = result;
	result = append_char(tmp, '$');
	return (result);
}

char	*process_dollar(char *res, const char *token, t_expand_con *con)
{
	if (token[*(con->i)] == '?')
		res = handle_question_mark(res, con);
	else if (token[*(con->i)] && is_valid_var_char(token[*(con->i)]))
		res = h_v(res, token, con->env, con);
	else
		res = handle_dollar(res);
	return (res);
}

char	*handle_backslash_dollar(char *result, const char *token,
		t_expand_con *context)
{
	(void)token;
	result = append_char(result, '$');
	if (!result)
		return (NULL);
	(*(context->i))++;
	return (result);
}

char	*handle_backslash_backslash(char *result, const char *token,
		t_expand_con *context)
{
	(void)token;
	result = append_char(result, '\\');
	if (!result)
		return (NULL);
	(*(context->i))++;
	return (result);
}

char	*handle_backslash_other(char *result, const char *token,
		t_expand_con *context)
{
	char	c;

	if (token[*(context->i)] != '\0')
	{
		c = token[*(context->i)];
		result = append_char(result, c);
		if (!result)
			return (NULL);
		(*(context->i))++;
	}
	return (result);
}
