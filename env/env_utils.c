/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:44:13 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 17:37:43 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

void	env_print(t_env *env)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (cur->printable)
			printf("%s\n", cur->var);
		cur = cur->next;
	}
}

t_env	*env_new_elem(char *var)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->printable = 1;
	new->var = ft_strdup(var);
	if (!new->var)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_env	*env_init(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		new = env_new_elem(envp[i]);
		if (!new)
		{
			env_free(head);
			return (NULL);
		}
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		i++;
	}
	return (head);
}
