/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:59:10 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 20:02:09 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*replace_variable(const char *name, t_env *env)
{
	char	*val;

	if (!name)
		return (ft_strdup(""));
	val = env_get_value(env, name);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

char	*str_append(const char *s1, const char *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, s1);
	ft_strcat(new_str, s2);
	return (new_str);
}

char	*append_char(char *result, char c)
{
	char	temp[2];
	char	*new_result;

	temp[0] = c;
	temp[1] = '\0';
	new_result = str_append(result, temp);
	if (!new_result)
	{
		free(result);
		return (NULL);
	}
	free(result);
	return (new_result);
}

char	*handle_question_mark(char *result, t_expand_con *context)
{
	char	buff[12];
	char	*tmp;
	size_t	tmp_len;
	size_t	buff_len;

	snprintf(buff, sizeof(buff), "%d", context->last_exit_code);
	tmp = result;
	tmp_len = ft_strlen(tmp);
	buff_len = strlen(buff);
	result = malloc(tmp_len + buff_len + 1);
	if (!result)
	{
		free(tmp);
		return (NULL);
	}
	ft_strcpy(result, tmp);
	ft_strcat(result, buff);
	free(tmp);
	(*(context->i))++;
	return (result);
}

char	*extract_varname(const char *token, int start, int len)
{
	char	*varname;

	varname = malloc(len + 1);
	if (!varname)
		return (NULL);
	ft_strncpy(varname, token + start, len);
	varname[len] = '\0';
	return (varname);
}
