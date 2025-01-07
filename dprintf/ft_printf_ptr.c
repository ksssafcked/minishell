/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:06:45 by lsaiti            #+#    #+#             */
/*   Updated: 2024/10/26 18:33:54 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptr_len(uintptr_t ptr)
{
	int	len;

	len = 0;
	while (ptr != 0)
	{
		len++;
		ptr /= 16;
	}
	return (len);
}

int	ft_put_ptr(int fd, uintptr_t ptr)
{
	int	len;

	len = ft_ptr_len(ptr);
	if (ptr >= 16)
	{
		ft_put_ptr(fd, ptr / 16);
		ft_put_ptr(fd, ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_printf_char(fd, (ptr + '0'));
		else
			ft_printf_char(fd, (ptr - 10 + 'a'));
	}
	return (len);
}

int	ft_printf_ptr(int fd, void *ptr)
{
	uintptr_t	address;
	int			i;

	i = 0;
	address = (uintptr_t)ptr;
	if (!ptr)
	{
		write (fd, "(nil)", 5);
		return (5);
	}
	write (fd, "0x", 2);
	i += 2;
	i += ft_put_ptr(fd, address);
	return (i);
}
