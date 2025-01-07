/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:16:21 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 18:30:16 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	total_len;
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((total_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strnstr(const char *big, const char *little, unsigned int len)
{
	int				i;
	unsigned int	j;

	j = 0;
	if (!*little)
		return ((char *)big);
	while (*big && j < len)
	{
		i = 0;
		if (big[i] == little[i])
		{
			while (big[i] == little[i] && little[i] && big[i] && (j + i < len))
			{
				i++;
			}
			if (little[i] == '\0')
				return ((char *)big);
		}
		j++;
		big++;
	}
	return (0);
}
