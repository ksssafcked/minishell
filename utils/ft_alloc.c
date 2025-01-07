/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:22:14 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 18:26:47 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

void	*ft_memcpy(void *dest_str, const void *src_str, size_t n)
{
	const unsigned char	*src;
	unsigned char		*dest;
	size_t				i;

	dest = (unsigned char *)dest_str;
	src = (const unsigned char *)src_str;
	if (dest == src || n == 0)
		return (dest_str);
	i = 0;
	while (n > i)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest_str);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)str;
	while (n > i)
		ptr[i++] = (unsigned char)c;
	return (str);
}

void	*ft_calloc(size_t num, size_t size)
{
	unsigned char	*str;
	size_t			total_size;

	total_size = num * size;
	str = (unsigned char *)malloc(total_size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, total_size);
	return (str);
}
