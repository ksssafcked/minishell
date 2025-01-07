/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:25:14 by lsaiti            #+#    #+#             */
/*   Updated: 2024/10/28 14:32:31 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

int	ft_dprintf(int fd, const char *str, ...)
	__attribute__ ((format(printf, 2, 3)));
int	ft_printf_read_param(int fd, char *str, va_list arg);
int	ft_printf_address_hex(int fd, va_list arg, char c);
int	ft_printf_unsigned_int(int fd, unsigned int nbr);
int	ft_printf_str(int fd, char *s);
int	ft_printf_ptr(int fd, void *ptr);
int	ft_printf_nbr(int fd, int n);
int	ft_printf_char(int fd, char c);
int	ft_printf_base_unsigned(int fd, unsigned int nbr, char *base);

#endif