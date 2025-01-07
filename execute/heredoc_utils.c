/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:55:33 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 17:38:06 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_heredoc_quoted(const char *delim)
{
	size_t	len;

	if (!delim)
		return (0);
	len = ft_strlen(delim);
	if (len < 2)
		return (0);
	if (delim[0] == '\'' && delim[len - 1] == '\'')
		return (1);
	if (delim[0] == '"' && delim[len - 1] == '"')
		return (1);
	return (0);
}

char	*remove_quotes(const char *str)
{
	size_t	len;
	char	*new_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2)
	{
		if ((str[0] == '\'' && str[len - 1] == '\'')
			|| (str[0] == '"' && str[len - 1] == '"'))
		{
			new_str = malloc(len - 1);
			if (!new_str)
				return (NULL);
			ft_strncpy(new_str, str + 1, len - 2);
			new_str[len - 2] = '\0';
			return (new_str);
		}
	}
	return (ft_strdup(str));
}

int	w_to_p(int fd, const char *line, int h_q, t_expand_context *c)
{
	char	*expanded;

	if (!h_q)
	{
		expanded = expand_token(line, c->env, c->last_exit_code);
		if (!expanded)
			return (-1);
		if (ft_dprintf(fd, "%s\n", expanded) < 0)
		{
			free(expanded);
			return (-1);
		}
		free(expanded);
	}
	else
	{
		if (ft_dprintf(fd, "%s\n", line) < 0)
			return (-1);
	}
	return (0);
}
