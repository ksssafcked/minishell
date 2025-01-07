/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 16:25:33 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 17:59:06 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_substr_custom(const char *s, unsigned int start)
{
	char	*extract;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s + start);
	extract = malloc(sizeof(char) * (len + 1));
	if (!extract)
		return (NULL);
	i = 0;
	while (i < len)
	{
		extract[i] = s[start + i];
		i++;
	}
	extract[len] = '\0';
	return (extract);
}

int	cmp_strings(const void *a, const void *b)
{
	char *const	*sa;
	char *const	*sb;

	sa = (char *const *)a;
	sb = (char *const *)b;
	return (ft_strcmp(*sa, *sb));
}

size_t	has_value(char *str)
{
	while (*str && *str != '=')
		str++;
	if (*str != '=')
		return (0);
	return (1);
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	is_builtin_cmd(char **argv)
{
	if (!argv || !argv[0])
		return (0);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (1);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(argv[0], "export") == 0)
		return (1);
	if (ft_strcmp(argv[0], "unset") == 0)
		return (1);
	if (ft_strcmp(argv[0], "env") == 0)
		return (1);
	if (ft_strcmp(argv[0], "exit") == 0)
		return (1);
	return (0);
}
