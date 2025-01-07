/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:16 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 18:26:53 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	ft_bzero(void *dst, size_t n)
{
	unsigned char	*zero;
	size_t			i;

	i = 0;
	zero = (unsigned char *)dst;
	while (n > i)
	{
		zero[i] = 0;
		i++;
	}
}

void	ft_swap_bytes(unsigned char *a, unsigned char *b, size_t size)
{
	size_t			i;
	unsigned char	tmp;

	i = 0;
	while (i < size)
	{
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
		i++;
	}
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	len;

	i = 0;
	while (dest[i])
		i++;
	len = 0;
	while (src[len])
	{
		dest[i] = src[len];
		i++;
		len++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
