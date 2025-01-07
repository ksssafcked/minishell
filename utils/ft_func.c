/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:19:29 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/29 18:45:25 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

int	f(unsigned char *base, size_t size, int (*cmp)(const void *, const void *),
		t_indices lr)
{
	int	pivot;
	int	i;
	int	j;

	pivot = lr.right;
	i = lr.left - 1;
	j = lr.left;
	while (j < pivot)
	{
		if (cmp((void *)(base + j * size), (void *)(base + pivot * size)) <= 0)
		{
			i++;
			ft_swap_bytes(base + i * size, base + j * size, size);
		}
		j++;
	}
	i++;
	ft_swap_bytes(base + i * size, base + pivot * size, size);
	return (i);
}

void	ft(unsigned char *base, size_t size, int (*cmp)(const void *,
			const void *), t_indices lr)
{
	int			partition_index;
	t_indices	left_lr;
	t_indices	right_lr;

	if (lr.left >= lr.right)
		return ;
	partition_index = f(base, size, cmp, lr);
	left_lr.left = lr.left;
	left_lr.right = partition_index - 1;
	ft(base, size, cmp, left_lr);
	right_lr.left = partition_index + 1;
	right_lr.right = lr.right;
	ft(base, size, cmp, right_lr);
}

void	ft_qsort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *,
			const void *))
{
	t_indices	lr;

	if (!base)
		return ;
	if (nmemb < 2)
		return ;
	if (size == 0)
		return ;
	if (!cmp)
		return ;
	lr.left = 0;
	lr.right = (int)(nmemb - 1);
	ft((unsigned char *)base, size, cmp, lr);
}

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long	result;
	int		sign;

	if (base != 10)
		base = 10;
	while (ft_isspace((unsigned char)*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (ft_isdigit((unsigned char)*str))
	{
		result = result * base + (*str - '0');
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}
