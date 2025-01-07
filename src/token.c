/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:21:17 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 19:22:04 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_tokens_quotes(char **tokens, t_shell *shell, int idx)
{
	char	*expanded;
	char	*tmp;

	if (is_simple_quote(tokens[idx]))
	{
		tmp = delete_quote(tokens[idx]);
		tokens[idx] = tmp;
	}
	else if (is_double_quote(tokens[idx]))
	{
		tmp = delete_quote(tokens[idx]);
		expanded = expand_token(tmp, shell->env, shell->last_exit_code);
		free(tmp);
		tokens[idx] = expanded;
	}
}

void	remove_empty_tokens(char **tokens, int *idx)
{
	int	j;

	if (ft_strlen(tokens[0]) == 0)
	{
		free(tokens[0]);
		j = 0;
		while (tokens[j])
		{
			tokens[j] = tokens[j + 1];
			j++;
		}
		(*idx)--;
	}
}

void	expand_and_clean_tokens(char **tokens, t_shell *shell)
{
	int		idx;
	char	*tmp;
	char	*expanded;

	idx = 0;
	while (tokens[idx])
	{
		if (is_simple_quote(tokens[idx]) || is_double_quote(tokens[idx]))
			expand_tokens_quotes(tokens, shell, idx);
		else
		{
			tmp = delete_quote(tokens[idx]);
			expanded = expand_token(tmp, shell->env, shell->last_exit_code);
			free(tmp);
			tokens[idx] = expanded;
			remove_empty_tokens(&tokens[idx], &idx);
		}
		idx++;
	}
}

char	**tokenize_input(char *line)
{
	char	**tokens;

	tokens = tokenize_line(line);
	return (tokens);
}

int	validate_tokens(char **tokens, t_shell *shell, char *line)
{
	int	count_tok;

	count_tok = count_tokens(tokens);
	if (!check_syntax(tokens, count_tok, shell))
	{
		free(line);
		return (0);
	}
	expand_and_clean_tokens(tokens, shell);
	if (!tokens[0])
	{
		free_tokens(tokens);
		free(line);
		return (0);
	}
	return (1);
}
