/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:12:25 by lsaiti            #+#    #+#             */
/*   Updated: 2024/10/28 15:12:04 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_in_it(char c, char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == c)
			return (1);
		j++;
	}
	return (0);
}

int	ft_printf_address_hex(int fd, va_list arg, char c)
{
	char	*hex;
	char	*hex2;

	hex = "0123456789abcdef";
	hex2 = "0123456789ABCDEF";
	if (c == 'x')
		return (ft_printf_base_unsigned(fd, va_arg(arg, unsigned int), hex));
	else if (c == 'X')
		return (ft_printf_base_unsigned(fd, va_arg(arg, unsigned int), hex2));
	return (0);
}

int	ft_printf_read_param(int fd, char *str, va_list arg)
{
	if (!str)
		return (0);
	if (str[0] == 'i')
		return (ft_printf_nbr(fd, va_arg(arg, int)));
	else if (str[0] == 'd')
		return (ft_printf_nbr(fd, va_arg(arg, int)));
	else if (str[0] == 'c')
		return (ft_printf_char(fd, (char)va_arg(arg, int)));
	else if (str[0] == 's')
		return (ft_printf_str(fd, va_arg(arg, char *)));
	else if (str[0] == 'u')
		return (ft_printf_unsigned_int(fd, va_arg(arg, unsigned int)));
	else if (str[0] == '%')
		return (ft_printf_char(fd, '%'));
	else if (str[0] == 'x' || str[0] == 'X')
		return (ft_printf_address_hex(fd, arg, str[0]));
	else if (str[0] == 'p')
		return (ft_printf_ptr(fd, va_arg(arg, void *)));
	else
		return (0);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	args;
	int		i;
	char	*conversions;

	i = 0;
	if (fd < 0)
		return (0);
	va_start (args, str);
	conversions = "cspdiuxX%";
	while (str && *str)
	{
		if (*str == '%' && ft_in_it(*(str + 1), conversions))
		{
			i += ft_printf_read_param(fd, (char *)(str + 1), args);
			str += 2;
		}
		else
		{
			ft_printf_char(fd, *(str++));
			i++;
		}
	}
	va_end(args);
	return (i);
}
