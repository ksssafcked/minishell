/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 15:31:10 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 17:38:23 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**process_tokens(const char *ptr, char **tokens, size_t count)
{
	char	*token;

	while (*ptr)
	{
		token = get_next_token(&ptr);
		if (!token)
			return (cleanup_tokens(tokens, count));
		if (!add_token(&tokens, &count, token))
			return (cleanup_tokens(tokens, count));
		skip_spaces(&ptr);
	}
	return (tokens);
}

char	**ft_split_line(char *line)
{
	char		*preprocessed;
	const char	*ptr;
	char		**tokens;

	if (!line)
		return (NULL);
	preprocessed = preprocess_line(line);
	if (!preprocessed)
		return (NULL);
	ptr = preprocessed;
	tokens = NULL;
	skip_spaces(&ptr);
	tokens = process_tokens(ptr, tokens, 0);
	free(preprocessed);
	return (tokens);
}

char	*delete_quote(char *line)
{
	size_t	len;
	char	*final;
	size_t	i;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len < 2)
	{
		free(line);
		return (ft_strdup(""));
	}
	final = malloc(sizeof(char) * (len));
	if (!final)
		return (free(line), NULL);
	i = 0;
	while (i < len - 1)
	{
		final[i] = line[i + 1];
		i++;
	}
	final[len - 1] = '\0';
	free(line);
	return (final);
}
