/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned_int.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:06:24 by lsaiti            #+#    #+#             */
/*   Updated: 2024/10/26 18:34:15 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_unsigned_int(int fd, unsigned int nbr)
{
	char	c;
	int		i;

	i = 0;
	if (nbr >= 10)
		i += ft_printf_unsigned_int(fd, nbr / 10);
	c = (nbr % 10) + '0';
	write (fd, &c, 1);
	i++;
	return (i);
}
