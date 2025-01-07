/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_base_unsigned.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:14:00 by lsaiti            #+#    #+#             */
/*   Updated: 2024/10/26 18:18:34 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_strlen(const char *str)
{
	int	compteur;

	compteur = 0;
	while (*(str++))
		compteur++;
	return (compteur);
}

static int	ft_in_it(int nb, char c, char *str)
{
	int	j;

	j = 0;
	while (j < nb)
	{
		if (str[j] == c)
			return (1);
		j++;
	}
	return (0);
}

static int	ft_valid_base(char *base)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	if (i == 0 || i == 1)
		return (0);
	i = 0;
	while (base[i])
	{
		if (ft_in_it(i, base[i], base) || (base[i] == '+' || base[i] == '-'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_printf_base_unsigned(int fd, unsigned int nbr, char *base)
{
	unsigned long	i;
	int				len_nbr;
	unsigned long	len;
	unsigned long	nb;

	len_nbr = 0;
	len = ft_strlen(base);
	nb = nbr;
	if (!ft_valid_base(base))
		return (0);
	if (nb >= len)
	{
		i = nb / len;
		len_nbr += ft_printf_base_unsigned(fd, i, base);
	}
	i = (nb % len);
	write(fd, &base[i], 1);
	len_nbr++;
	return (len_nbr);
}
