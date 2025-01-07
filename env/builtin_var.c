/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:30:02 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 17:37:41 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->var);
		free(node);
	}
}

t_env	*delete_node(t_env *prev, t_env *cur, t_env *env)
{
	t_env	*temp;

	if (prev == NULL)
	{
		temp = cur->next;
		free_env_node(cur);
		return (temp);
	}
	prev->next = cur->next;
	free_env_node(cur);
	return (env);
}

t_env	*remove_env_var(t_env *env, const char *var_name)
{
	t_env	*prev;
	t_env	*cur;

	prev = NULL;
	cur = env;
	while (cur != NULL)
	{
		if (is_matching_var(cur->var, var_name))
		{
			return (delete_node(prev, cur, env));
		}
		prev = cur;
		cur = cur->next;
	}
	return (env);
}

void	set_env_var(t_env *env, const char *new_var)
{
	char	*eq;
	size_t	var_len;
	t_env	*cur;

	eq = ft_strchr(new_var, '=');
	if (!eq)
		return ;
	var_len = eq - new_var;
	cur = env;
	while (cur)
	{
		if (!ft_strncmp(cur->var, new_var, var_len)
			&& (cur->var[var_len] == '='
				|| cur->var[var_len] == '\0'))
		{
			free(cur->var);
			cur->var = ft_strdup(new_var);
			cur->printable = 1;
			return ;
		}
		cur = cur->next;
	}
	env_add_var(env, new_var);
}

void	set_env_no_value(t_env *env, const char *new_var)
{
	size_t	var_len;
	t_env	*cur;

	var_len = ft_strlen(new_var);
	cur = env;
	while (cur)
	{
		if (!ft_strncmp(new_var, cur->var, var_len))
			return ;
		cur = cur->next;
	}
	env_add_var(env, new_var);
}
