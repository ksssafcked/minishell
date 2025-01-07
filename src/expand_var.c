/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:02:34 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 20:02:54 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_var_char(char c)
{
	if (c == '_')
		return (1);
	if (ft_isdigit(c))
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

char	*get_varname(const char *token, int *i, int *len)
{
	int		start;
	char	*varname;

	start = *i;
	while (token[*i] && is_valid_var_char(token[*i]))
		(*i)++;
	*len = *i - start;
	varname = extract_varname(token, start, *len);
	return (varname);
}

char	*append_var_value(char *result, const char *var_value)
{
	char	*tmp;
	char	*new_result;

	tmp = result;
	new_result = str_append(tmp, var_value);
	if (!new_result)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (new_result);
}

char	*h_v(char *result, const char *token, t_env *env, t_expand_con *con)
{
	int		len;
	char	*varname;
	char	*var_value;

	varname = get_varname(token, con->i, &len);
	if (!varname)
	{
		free(result);
		return (NULL);
	}
	var_value = replace_variable(varname, env);
	free(varname);
	if (!var_value)
	{
		free(result);
		return (NULL);
	}
	result = append_var_value(result, var_value);
	free(var_value);
	if (!result)
		return (NULL);
	return (result);
}
