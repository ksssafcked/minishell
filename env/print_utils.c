/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:51:12 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:51:35 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_env_variable(const char *env_var)
{
	char	*name;
	char	*value;
	int		needs_quotes;
	int		extract_result;

	name = NULL;
	value = NULL;
	extract_result = extract_name_value(env_var, &name, &value);
	if (extract_result == 1)
	{
		needs_quotes = value_needs_quotes(value);
		print_declare(name, value, needs_quotes);
		free(name);
		free(value);
	}
	else if (extract_result == 0)
	{
		printf("declare -x %s\n", env_var);
	}
}

void	sort_and_print(char **arr, int size)
{
	int	i;

	ft_qsort(arr, size, sizeof(char *), cmp_strings);
	i = 0;
	while (i < size)
	{
		print_env_variable(arr[i]);
		i++;
	}
}

void	print_export(t_env *env)
{
	char	**arr;
	int		size;

	arr = env_to_char_array(env);
	if (!arr)
		return ;
	size = env_size(env);
	sort_and_print(arr, size);
	free_array(arr, size);
}
