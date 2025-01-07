/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:32:32 by qudomino          #+#    #+#             */
/*   Updated: 2024/12/29 17:37:45 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*get_env_var(t_env *env, char *env_name)
{
	size_t	len;

	len = ft_strlen(env_name);
	while (env)
	{
		if (ft_strncmp(env->var, env_name, len) == 0 && env->var[len] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*env_add_var(t_env *env, const char *new_var)
{
	t_env	*cur;
	t_env	*new;

	cur = env;
	while (cur->next)
		cur = cur->next;
	new = env_new_elem((char *)new_var);
	if (!new)
		return (env);
	if (!ft_strchr(new_var, '='))
		new->printable = 0;
	cur->next = new;
	return (env);
}

char	*env_get_value(t_env *env, const char *name)
{
	size_t	len;

	len = ft_strlen(name);
	while (env)
	{
		if (ft_strncmp(env->var, name, len) == 0 && (env->var[len] == '='
				|| env->var[len] == '\0'))
			return (env->var + len + 1);
		env = env->next;
	}
	return (NULL);
}

char	**env_to_char_array(t_env *env)
{
	int		size;
	int		i;
	char	**arr;

	size = env_size(env);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i] = strdup(env->var);
		if (!arr[i])
		{
			free_array(arr, i);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
