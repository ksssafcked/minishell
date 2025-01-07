/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:21:23 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/03 16:30:20 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*unset_cmd(t_env *env, char **args)
{
	int	i;

	if (!args[1])
		return (env);
	i = 1;
	while (args[i])
	{
		env = remove_env_var(env, args[i]);
		i++;
	}
	return (env);
}

void	export_cmd(t_shell *shell, t_env *env, char **args)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	if (!args[1])
	{
		print_export(env);
		shell->last_exit_code = exit_code;
		return ;
	}
	i = 0;
	while (args[++i])
	{
		process_argument(env, args[i], &exit_code);
	}
	shell->last_exit_code = exit_code;
}

void	echo_cmd(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[i] && !ft_strcmp(args[i], "-"))
		i++;
	if (args[i] && is_nl_arg(args[i]))
	{
		newline = 0;
		i++;
		while (args[i] && is_nl_arg(args[i]))
			i++;
	}
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
}

int	exit_cmd(char **args, int last_exit_code, int *should_exit, t_env *env)
{
	int		arg_count;
	long	val;
	int		exit_code;

	arg_count = count_args(args);
	if (arg_count < 2)
	{
		*should_exit = 1;
		return (last_exit_code);
	}
	if (!is_numeric_argument(args[1]))
	{
		print_numeric_error(args[1], env);
		return (2);
	}
	if (arg_count > 2)
		return (print_too_many_args_error(), 1);
	errno = 0;
	val = ft_strtol(args[1], NULL, 10);
	if (errno == ERANGE)
		return (print_numeric_error(args[1], env), 2);
	*should_exit = 1;
	exit_code = (unsigned char)val;
	return (exit_code);
}
