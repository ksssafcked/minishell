/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:39:52 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 17:37:36 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_array(char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_env_and_exit(t_env *env, int code)
{
	env_free(env);
	exit(code);
}

void	env_free(t_env *env)
{
	t_env	*cur;
	t_env	*tmp;

	cur = env;
	while (cur)
	{
		tmp = cur->next;
		free(cur->var);
		free(cur);
		cur = tmp;
	}
}
