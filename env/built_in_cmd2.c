/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:23:28 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/03 16:17:15 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_cmd(t_env *env)
{
	env_print(env);
}

void	change_pwd(t_env *env, char *directory)
{
	char	*old_val;
	char	*tmp;
	t_env	*old_env;
	t_env	*pwd_env;

	old_env = get_env_var(env, "OLDPWD");
	pwd_env = get_env_var(env, "PWD");
	if (!pwd_env || !old_env)
		return ;
	old_val = ft_substr_custom(pwd_env->var, 4);
	free(old_env->var);
	{
		tmp = ft_strjoin("OLDPWD=", old_val);
		old_env->var = tmp;
	}
	free(old_val);
	free(pwd_env->var);
	pwd_env->var = ft_strjoin("PWD=", directory);
}

void	pwd_cmd(t_shell *shell)
{
	printf("%s\n", shell->directory);
}
