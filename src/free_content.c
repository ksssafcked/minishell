/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:11:38 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:12:23 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_argv(char **argv)
{
	int	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_command(t_command *c)
{
	if (c == NULL)
		return ;
	if (c->argv != NULL)
		free_argv(c->argv);
	free(c->infile);
	free(c->outfile);
	free(c->heredoc_delim);
	if (c->in_fd != -1)
		close(c->in_fd);
	if (c->out_fd != -1)
		close(c->out_fd);
	free(c);
}

void	free_pipeline(t_pipeline *pl)
{
	t_command	*c;
	t_command	*next;

	if (pl == NULL)
		return ;
	c = pl->commands;
	while (c != NULL)
	{
		next = c->next;
		free_command(c);
		c = next;
	}
	free(pl);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	*free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}
