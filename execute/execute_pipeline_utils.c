/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:59:45 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 18:00:06 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_commands(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	handle_error_file(const char *cmd)
{
	if (errno == EACCES)
		set_error_and_code(cmd, "Permission denied", 126);
	if (errno == ENOENT)
		set_error_and_code(cmd, "No such file or directory", 127);
	if (errno == EISDIR)
		set_error_and_code(cmd, "Is a directory", 127);
}
