/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:27:33 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:52:41 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_numeric_error(char *arg, t_env *env)
{
	ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", arg);
	free_env_and_exit(env, 2);
}

void	print_too_many_args_error(void)
{
	ft_dprintf(2, "minishell: exit: too many arguments\n");
}

int	value_needs_quotes(const char *v)
{
	size_t	i;

	i = 0;
	while (v[i] != '\0')
	{
		if (!isalnum((unsigned char)v[i]) && v[i] != '/' && v[i] != '_'
			&& v[i] != '-' && v[i] != ':')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_declare(const char *name, const char *value, int needs_quotes)
{
	if (needs_quotes)
	{
		printf("declare -x %s='%s'\n", name, value);
	}
	else
	{
		printf("declare -x %s=\"%s\"\n", name, value);
	}
}

int	extract_name_value(const char *env_var, char **name, char **value)
{
	const char	*eq;
	size_t		name_len;

	eq = ft_strchr(env_var, '=');
	if (!eq)
	{
		return (0);
	}
	name_len = eq - env_var;
	*name = ft_substr(env_var, 0, name_len);
	if (!(*name))
	{
		return (-1);
	}
	*value = ft_strdup(eq + 1);
	if (!(*value))
	{
		free(*name);
		*name = NULL;
		return (-1);
	}
	return (1);
}
