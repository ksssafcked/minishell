/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:34:50 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 17:37:34 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_matching_var(const char *var, const char *var_name)
{
	size_t	len;

	len = ft_strlen(var_name);
	return (ft_strncmp(var, var_name, len) == 0 && var[len] == '=');
}

int	is_numeric_argument(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!isdigit((unsigned char)arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_identifier(const char *var)
{
	int	i;

	if (!((var[0] >= 'a' && var[0] <= 'z') || (var[0] >= 'A' && var[0] <= 'Z')
			|| var[0] == '_'))
		return (0);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!((var[i] >= 'a' && var[i] <= 'z') || (var[i] >= 'A'
					&& var[i] <= 'Z') || (var[i] >= '0' && var[i] <= '9')
				|| var[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
